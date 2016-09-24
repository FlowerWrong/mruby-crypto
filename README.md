# mruby-crypto   [![Build Status](https://travis-ci.org/FlowerWrong/mruby-crypto.svg?branch=master)](https://travis-ci.org/FlowerWrong/mruby-crypto)
Crypto class

## install by mrbgems
- add conf.gem line to `build_config.rb`

```ruby
MRuby::Build.new do |conf|

    # ... (snip) ...

    conf.gem :github => 'FlowerWrong/mruby-crypto'
end
```

## test

```
ruby run_test.rb
rake test
```

## example
```ruby
p Crypto.hi
#=> "hi!!"
t = Crypto.new "hello"
p t.hello
#=> "hello"
p t.bye
#=> "hello bye"
```

## License
under the MIT License:
- see LICENSE file
