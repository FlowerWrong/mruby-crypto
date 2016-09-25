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
def method_supported(method)
  case method
    when 'aes-128-cfb'      then [16, 16]
    when 'aes-192-cfb'      then [24, 16]
    when 'aes-256-cfb'      then [32, 16]
    when 'bf-cfb'           then [16, 8 ]
    when 'camellia-128-cfb' then [16, 16]
    when 'camellia-192-cfb' then [24, 16]
    when 'camellia-256-cfb' then [32, 16]
    when 'cast5-cfb'        then [16, 8 ]
    when 'des-cfb'          then [8,  8 ]
    when 'idea-cfb'         then [16, 8 ]
    when 'rc2-cfb'          then [16, 8 ]
    when 'rc4'              then [16, 0 ]
    when 'seed-cfb'         then [16, 16]
  end
end

def test_encrypt_and_decrypt
  methods = ['aes-128-cfb', 'aes-192-cfb', 'aes-256-cfb', 'bf-cfb', 'camellia-128-cfb', 'camellia-192-cfb', 'camellia-256-cfb', 'cast5-cfb', 'des-cfb', 'idea-cfb', 'rc2-cfb', 'rc4', 'seed-cfb']
  methods.each do |m|
    key_len, iv_len = method_supported(m)
    key = 'k' * key_len
    iv =  'k' * iv_len
    msg = 'hello'
    cipher = ::Cipher.new(m, key, iv, :encrypt)
    en_data = cipher.update(msg)
    cipher.type = :decrypt
    data = cipher.update(en_data)
    p (msg == data)
  end
end
test_encrypt_and_decrypt
```

## License
under the MIT License:
- see LICENSE file
