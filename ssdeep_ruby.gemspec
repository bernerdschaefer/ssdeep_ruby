spec = Gem::Specification.new do |s|
  s.name = "ssdeep_ruby"
  s.summary = s.description = "Ruby bindings for ssdeep"
  s.author = "Bernerd Schaefer"
  s.email = "bj.schaefer@gmail.com"
  s.version = "1.0"
  s.platform = Gem::Platform::RUBY
  s.require_path = 'lib'
  s.extensions << 'ext/extconf.rb'
  s.files = %w(Rakefile) + Dir.glob("lib/**/*")
end
