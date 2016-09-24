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

  def test_hi
    assert_equal("hi!!", Crypto.hi)
  end
end

if $ok_test
  MTest::Unit.new.mrbtest
else
  MTest::Unit.new.run
end
