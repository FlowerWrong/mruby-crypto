##
## Crypto Test
##

assert("Crypto#hello") do
  t = Crypto.new "hello"
  assert_equal("hello", t.hello)
end

assert("Crypto#bye") do
  t = Crypto.new "hello"
  assert_equal("hello bye", t.bye)
end

assert("Crypto.hi") do
  assert_equal("hi!!", Crypto.hi)
end
