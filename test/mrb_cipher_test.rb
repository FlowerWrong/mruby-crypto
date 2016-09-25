class MrbCipherTest < MTest::Unit::TestCase
  def setup
  end

  def test_encrypt_and_decrypt
    methods = ['aes-128-cfb', 'aes-192-cfb', 'aes-256-cfb', 'bf-cfb', 'camellia-128-cfb', 'camellia-192-cfb', 'camellia-256-cfb', 'cast5-cfb', 'des-cfb', 'idea-cfb', 'rc2-cfb', 'rc4', 'seed-cfb']
    methods.each do |m|
      key_len, iv_len = Crypto.cipher_len(m)
      key = 'k' * key_len
      iv =  'k' * iv_len
      msg = 'hello'
      cipher = ::Cipher.new(m, key, iv, :encrypt)
      en_data = cipher.update(msg)
      cipher.type = :decrypt
      data = cipher.update(en_data)
      assert_equal(msg, data)
    end
  end
end

if $ok_test
  MTest::Unit.new.mrbtest
else
  MTest::Unit.new.run
end
