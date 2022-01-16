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

package main

import (
    "fmt"
    "log"
    "net/http"
    "os"
    "time"

    "github.com/alecthomas/kong"
    "github.com/poiredb/poiredb/pkg/pql"
    "github.com/poiredb/poiredb/pkg/util"
)

var cli struct {
    Host string `default:"127.0.0.1"`
    Port string `default:"8080"`
}

func main() {
    ctx := kong.Parse(&cli,
        kong.Name("poiredb"),
        kong.Description("PoireDB server."))

    http.HandleFunc("/lex", func(w http.ResponseWriter, r *http.Request) {
        now := time.Now()
        fn, out := pql.Lex(r.URL.Query().Get("input"))
        w.Write([]byte(out))
        log.Println("done in", time.Since(now))
        log.Println("remove", fn)
        err := os.Remove(fn)
        util.Check(err)
    })

    log.Fatal(
        http.ListenAndServe(fmt.Sprintf("%s:%s", cli.Host, cli.Port), nil))

    _ = ctx
}
