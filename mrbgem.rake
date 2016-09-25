MRuby::Gem::Specification.new('mruby-crypto') do |spec|
  spec.license = 'MIT'
  spec.authors = 'yang'

  # spec.add_dependency 'mruby-io'
  unless ENV['test'] == 'yes'
    openssl_dir = File.join(build_dir, 'openssldir')
    spec.cc.include_paths << "#{openssl_dir}/include"
    spec.linker.library_paths << "#{openssl_dir}/lib"

    spec.linker.libraries << 'ssl'
    spec.linker.libraries << 'crypto'
  end
end
