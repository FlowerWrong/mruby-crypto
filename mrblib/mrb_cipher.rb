class Cipher
  attr_accessor :method, :key, :iv, :type

  def initialize(method = nil, key = nil, iv = nil, type = nil)
    @method = method
    @key = key
    @iv = iv
    @type = type
  end

  def key_iv_len
    Crypto.cipher_len(@method)
  end

  def update(data = nil)
    key_len, iv_len = key_iv_len
    raise "key len must be #{key_len}, now #{key.size}; iv len must be #{iv_len}, now #{iv.size}" if key.size != key_len || iv.size != iv_len
    if @type == :encrypt
      Crypto.encrypt(@method, data, key, iv)
    elsif @type == :decrypt
      Crypto.decrypt(@method, data, key, iv)
    else
      raise 'No support for this type'
    end
  end
end
