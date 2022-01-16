/**
 * MIT License
 * Copyright (c) 2022 PoireDB authors and contributors
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal in the Software without restriction, including without limitation the
 * rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
 * sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

package pql

import (
    "io/ioutil"
    "log"
    "os/exec"

    "github.com/poiredb/poiredb/pkg/util"
)

func check(err error) {
    if err != nil {
        log.Fatal(err)
    }
}

func Lex(input string) (string, string) {
    filename := util.TempFileName("", ".pql")

    err := ioutil.WriteFile(filename, []byte(input), 0644)
    util.Check(err)

    cmd := exec.Command("pql_lex", filename)
    log.Println("lex", filename)
    util.Check(err)

    out, err := cmd.Output()
    util.Check(err)

    return filename, string(out)
}
