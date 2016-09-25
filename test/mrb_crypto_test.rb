##
## Crypto Test
##

class MrbCrypotTest < MTest::Unit::TestCase
  def setup
    @methods = ['aes-128-cfb', 'aes-192-cfb', 'aes-256-cfb', 'bf-cfb', 'camellia-128-cfb', 'camellia-192-cfb', 'camellia-256-cfb', 'cast5-cfb', 'des-cfb', 'idea-cfb', 'rc2-cfb', 'rc4', 'seed-cfb']
  end

  def test_cipher_len
    @methods.each do |m|
      assert_equal(method_supported(m), Crypto.cipher_len(m))
    end
  end

  def test_encrypt_and_decrypt
    @methods.each do |m|
      key_len, iv_len = Crypto.cipher_len(m)
      key = 'k' * key_len
      iv =  'k' * iv_len
      msg = 'hello'
      en_data = Crypto.encrypt(m, msg, key, iv)
      data = Crypto.decrypt(m, en_data, key, iv)
      assert_equal(msg, data)
    end
  end

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
end

if $ok_test
  MTest::Unit.new.mrbtest
else
  MTest::Unit.new.run
end
