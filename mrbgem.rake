MRuby::Gem::Specification.new('mruby-crypto') do |spec|
  spec.license = 'MIT'
  spec.authors = 'yang'

  # spec.add_dependency 'mruby-io'
  spec.cc.include_paths += ['/usr/local/opt/openssl/include']
  spec.linker.library_paths += ['/usr/local/opt/openssl/lib']
  spec.linker.libraries += ['crypto']
end
