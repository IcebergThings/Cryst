// Copyright 2016 Iceberg OS
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//=============================================================================
// ■ string.c
//-----------------------------------------------------------------------------
//   内核字符串库
//=============================================================================

char* itoa(int value, char* result, int base) {
 // check that the base if valid
 if (base < 2 || base > 36) { *result = '\0'; return result; }

 char* ptr = result, *ptr1 = result, tmp_char;
 int tmp_value;

 do {
	 tmp_value = value;
	 value /= base;
	 *ptr++ = "zyxwvutsrqponmlkjihgfedcba9876543210123456789abcdefghijklmnopqrstuvwxyz" [35 + (tmp_value - value * base)];
 } while (value);

 // Apply negative sign
 if (tmp_value < 0) *ptr++ = '-';
 *ptr-- = '\0';
 while(ptr1 < ptr) {
	 tmp_char = *ptr;
	 *ptr--= *ptr1;
	 *ptr1++ = tmp_char;
 }
 return result;
}
