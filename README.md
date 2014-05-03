## Description

In my work I used to use BASE-64 encoders/decoders almost everytime. There are very important to me and definitely need to be 100% accurate. But sometimes I got a strange errors in code just because of mistakes in BASE-64 realizations. Finally I got a time (and necessity!) for implementing my own simple BASE-64 coder/decoder. The code could be compiled into a single *.exe file.

## Usage
```
 BASE-64 coder/decoder, v1.0
 (c) 2014, Yury Strozhevsky, www.strozhevsky.com
 
 Usage:;
 	b64.exe -e <file to encode> <output file>
 	b64.exe -ed <file to encode> <output file with 64-length strings>
 	b64.exe -d <file to decode> <output file>
```

## License

Copyright (c) 2014, [Yury Strozhevsky](http://www.strozhevsky.com)
All rights reserved.

Redistribution and use in source and binary forms, with or without
modification, are permitted provided that the following conditions are met:

* Redistributions of source code must retain the above copyright notice, this
  list of conditions and the following disclaimer.

* Redistributions in binary form must reproduce the above copyright notice,
  this list of conditions and the following disclaimer in the documentation
  and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.