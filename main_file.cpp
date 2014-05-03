#include <iostream>
#include <iterator>
#include <fstream>
#include <vector>
//********************************************************************************************
char* keyStr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/=";
//********************************************************************************************
int indexof( char toSearch )
{
 for( int i = 0; i < 64; i++ )
 {
  if( keyStr[i] == toSearch )
   return i;
 }

 return 64;
}
//********************************************************************************************
unsigned char test( unsigned char incoming )
{
 return ( ( incoming == 64 ) ? 0x00 : incoming );
}
//********************************************************************************************
int base64_encode( unsigned char* input, int input_len, unsigned char* output, int output_len )
{
 unsigned char chr1, chr2, chr3;
 unsigned char enc1, enc2, enc3, enc4;

 int i = 0;
 int j = 0;

 int flag1 = 0;
 int flag2 = 0;

 while( i < input_len )
 {
  chr1 = input[ i++ ];
  if( i >= input_len )
   flag1 = 1;
  chr2 = input[ i++ ];
  if( i >= input_len )
   flag2 = 1;
  chr3 = input[ i++ ];

  enc1 = chr1 >> 2;
  enc2 = ( ( chr1 & 0x03 ) << 4 ) | ( chr2 >> 4 );
  enc3 = ( ( chr2 & 0x0F ) << 2 ) | ( chr3 >> 6 );
  enc4 = chr3 & 0x3F;

  if( flag1 == 1 )
   enc3 = enc4 = 64;
  else 
  {
   if( flag2 == 1 )
    enc4 = 64;
  }

  output[ j++ ] = keyStr[ enc1 ];
  output[ j++ ] = keyStr[ enc2 ];
  output[ j++ ] = keyStr[ enc3 ];
  output[ j++ ] = keyStr[ enc4 ];
 }

 return j;
}
//********************************************************************************************
int base64_decode( unsigned char* input, int input_len, unsigned char* output, int output_len )
{
 unsigned char chr1, chr2, chr3;
 unsigned char enc1, enc2, enc3, enc4;

 int i = 0;
 int j = 0;

 while( i < input_len )
 {
  enc1 = indexof( input[ i++ ] );
  enc2 = ( i >= input_len ) ? 0x00 : indexof( input[ i++ ] );
  enc3 = ( i >= input_len ) ? 0x00 : indexof( input[ i++ ] );
  enc4 = ( i >= input_len ) ? 0x00 : indexof( input[ i++ ] );

  chr1 = ( test( enc1 ) << 2 ) | ( test( enc2 ) >> 4 );
  chr2 = ( ( test( enc2 ) & 0x0F ) << 4 ) | ( test( enc3 ) >> 2 );
  chr3 = ( ( test( enc3 ) & 0x03 ) << 6 ) | test( enc4 );

  output[ j++ ] = chr1;

  if( enc3 != 64 )
   output[ j++ ] = chr2;

  if( enc4 != 64 )
   output[ j++ ] = chr3;
 }

 return j;
}
//********************************************************************************************
void usage()
{
 std::cout << "BASE-64 coder/decoder, v1.0" << std::endl;
 std::cout << "(c) 2014, Yury Strozhevsky, www.strozhevsky.com" << std::endl;
 std::cout << std::endl << "Usage:" << std::endl;
 std::cout << "\tb64.exe -e <file to encode> <output file>" << std::endl;
 std::cout << "\tb64.exe -ed <file to encode> <output file with 64-length strings>" << std::endl;
 std::cout << "\tb64.exe -d <file to decode> <output file>" << std::endl;
}
//********************************************************************************************
void encode_file( char* input_file, char* output_file, bool divide )
{
 #pragma region Read input file into a buffer
  std::ifstream in_file( input_file, std::ios_base::binary );
  if( !in_file.good() )
   return;
  in_file.unsetf( std::ios_base::skipws );

  std::istreambuf_iterator< char > _in_iterator( in_file );
  std::istreambuf_iterator< char > _end_of_in;

  std::vector< char > input_buffer;

  std::copy( _in_iterator, _end_of_in, std::back_inserter( input_buffer ) );

  in_file.close();

  int input_buffer_size = input_buffer.size();

  unsigned char* output_buffer = ( unsigned char* )malloc( input_buffer_size * 3 );
  memset( output_buffer, 0, input_buffer_size * 3 );
 #pragma endregion

 #pragma region Encode input buffer
 int output_length = base64_encode( ( unsigned char* )&input_buffer[0], input_buffer_size, output_buffer, input_buffer_size * 3 );
 #pragma endregion

 #pragma region Initialization of output file
 std::ofstream out_file( output_file, std::ios_base::binary ); 
 std::ostream_iterator< char > _out_iterator( out_file );
 #pragma endregion

 #pragma region Divide output down to 63 chars if needed
 if( divide )
 {
  int sum_len = 0;
  int part_size = 0;

  while( sum_len < output_length )
  {
   part_size = ( ( sum_len + 64 ) > output_length ) ? ( output_length - sum_len ) : 64;

   std::copy( output_buffer + sum_len, output_buffer + sum_len + part_size, *_out_iterator );
   _out_iterator = '\r';
   _out_iterator = '\n';
   
   sum_len += part_size;
  }
 }
 else
  std::copy( output_buffer, output_buffer + output_length, *_out_iterator );
 #pragma endregion

 #pragma region Close all handlers
 free( output_buffer );

 out_file.flush();
 out_file.close();
 #pragma endregion
}
//********************************************************************************************
void decode_file( char* input_file, char* output_file )
{
 #pragma region Read input file into a buffer
 std::ifstream in_file( input_file, std::ios_base::binary );
 if( !in_file.good() )
  return;
 in_file.unsetf( std::ios_base::skipws );

 std::istreambuf_iterator< char > _in_iterator( in_file );
 std::istreambuf_iterator< char > _end_of_in;

 std::vector< char > input_buffer;

 std::copy( _in_iterator, _end_of_in, std::back_inserter( input_buffer ) );

 in_file.close();
 #pragma endregion

 #pragma region Remove all "\r\n" chars
 std::vector< char > input_buffer_clear;

 for( std::vector< char >::iterator i = input_buffer.begin(); i != input_buffer.end(); i++)
 {
  if( ( *i != '\r' ) && ( *i != '\n' ) )
   input_buffer_clear.push_back( *i );
 }

 int input_length = input_buffer_clear.size();
 #pragma endregion

 #pragma region Decode buffer
 unsigned char* output_buffer = ( unsigned char* )malloc( input_length );
 memset( output_buffer, 0, input_length );

 int output_length = base64_decode( ( unsigned char* )&input_buffer_clear[0], input_length, output_buffer, input_length );
 #pragma endregion

 #pragma region Store output buffer to external file
 std::ofstream out_file( output_file, std::ios_base::binary ); 
 std::ostream_iterator< char > _out_iterator( out_file );

 std::copy( output_buffer, output_buffer + output_length, *_out_iterator );
 #pragma endregion

 #pragma region Close all handlers
 free( output_buffer );

 out_file.flush();
 out_file.close();
 #pragma endregion
}
//********************************************************************************************
int main( int argc, char** argv )
{
 if(argc != 4)
 {
  usage();
  return 0;
 }

 if(strcmp(argv[1], "-e") == 0)
  encode_file( argv[2], argv[3], false );
 if(strcmp(argv[1], "-ed") == 0)
  encode_file( argv[2], argv[3], true );
 if(strcmp(argv[1], "-d") == 0)
  decode_file( argv[2], argv[3] );

 return 0;
}
//********************************************************************************************
