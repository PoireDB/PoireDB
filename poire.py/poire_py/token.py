# MIT License
# Copyright (c) 2022 PoireDB authors and contributors
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to
# deal in the Software without restriction, including without limitation the
# rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
# sell copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
# FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
# IN THE SOFTWARE.

import enum
from iota import iota
from dataclasses import dataclass

counter = -1

class TokenType(enum.Enum):
	COMMENT = iota()
  	VSTRING = iota()
  	VCHARACTER = iota()
  	VNUMBER = iota()
  	VBOOLEAN = iota()
  	KEYWORD = iota()
  	PUNCTUATOR = iota()
  	IDENTIFIER = iota()
  	_EOF = iota()
  	ERROR = iota()

@dataclass
class TokenPosition:
	Index: int
	Line: int
	Column: int

@dataclass
class TokenValue:
	String: str
	Number: float
	Character: str
	Boolean: bool

@dataclass
class Token:
	Type: TokenType
	Value: TokenValue
	StartPosition: TokenPosition
	EndPosition: TokenPosition