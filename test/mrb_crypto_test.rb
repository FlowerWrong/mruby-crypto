##
## Crypto Test
##

class MrbCrypotTest < MTest::Unit::TestCase
  def setup
  end

  def test_hello
    t = Crypto.new "hello"
    assert_equal("hello", t.hello)
  end

  def test_bye
    t = Crypto.new "hello"
    assert_equal("hello bye", t.bye)
  end

  def test_encrypt
    en_data = Crypto.encrypt('aes-256-cfb', 'hello', 'kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk', 'kkkkkkkkkkkkkkkk')
    data = Crypto.decrypt('aes-256-cfb', en_data, 'kkkkkkkkkkkkkkkkkkkkkkkkkkkkkkkk', 'kkkkkkkkkkkkkkkk')
    assert_equal('hello', data)
  end
end

if $ok_test
  MTest::Unit.new.mrbtest
else
  MTest::Unit.new.run
end
