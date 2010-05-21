require 'rubygems'
require 'rake'
require 'rake/clean'
require 'rake/testtask'
require 'rake/gempackagetask'
require 'rbconfig'

CLEAN.include("**/*.bundle")
CLEAN.include("ext/Makefile")
CLEAN.include("ext/*.dSYM")
CLEAN.include("ext/*.log")
CLEAN.include("ext/*.o")

task :default => [:compile, :test]

Rake::TestTask.new do |t|
  t.libs << "test"
  t.test_files = FileList['test/**/*_test.rb']
  t.verbose = true
end

extension_name = "ssdeep_ruby_ext.#{RbConfig::CONFIG['DLEXT']}"

directory 'lib'

file "lib/#{extension_name}" => ['lib', "ext/#{extension_name}"] do
  cp "ext/#{extension_name}", "lib/#{extension_name}"
end

task :compile => [:clean, "lib/#{extension_name}"]

file "ext/#{extension_name}" => FileList["ext/Makefile", "ext/*.c", "ext/*.h"] do
  Dir.chdir("ext") do
    sh "make"
  end
end

file "ext/Makefile" => "ext/extconf.rb" do
  Dir.chdir("ext") do
    ruby "extconf.rb"
  end
end

## GEM ##
NAME = "ssdeep_ruby"
SUMMARY = "Ruby bindings for ssdeep"
GEM_VERSION = "0.1"

spec = Gem::Specification.new do |s|
  s.name = NAME
  s.summary = s.description = SUMMARY
  s.author = "Bernerd Schaefer"
  s.email = "bj.schaefer@gmail.com"
  s.version = GEM_VERSION
  s.platform = Gem::Platform::RUBY
  s.require_path = 'lib'
  s.extensions << 'ext/extconf.rb'
  s.files = %w(Rakefile) + Dir.glob("lib/**/*")
end

Rake::GemPackageTask.new(spec) do |pkg|
  pkg.gem_spec = spec
end

desc "Install #{NAME} as a gem"
task :install => [:repackage] do
  sh %{gem install pkg/#{NAME}-#{GEM_VERSION}}
end
