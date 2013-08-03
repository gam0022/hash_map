# 何がしたかったのか

Rubyの `Hash#map` の挙動が気に入らなかったので、自作しました。

次のように使います。

```
require 'hash_map'

h = {:a => 0, :b => 1, :c => 2} # => {:a=>0, :b=>1, :c=>2}
h.map_to_hash{|a| a*2}          # => {:a=>0, :b=>2, :c=>4}
h                               # => {:a=>0, :b=>2, :c=>4}
```


## その他

* 調べてみたら、`Hash#map`だと思っていたものは、`Enumerable#map`だった。
* `Hash#map_to_hash`は長い?
