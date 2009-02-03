if RUBY_PLATFORM =~ /darwin/
  ENV["RC_ARCHS"] = `uname -m`.chomp if `uname -sr` =~ /^Darwin/

  # On PowerPC the defaults are fine
  ENV["RC_ARCHS"] = '' if `uname -m` =~ /^Power Macintosh/
end

require 'mkmf'

$CFLAGS << ' -Wall ' unless RUBY_PLATFORM =~ /mswin/

if have_header( "fuzzy.h" ) && have_library("fuzzy", "fuzzy_hash_buf")
  create_makefile("ssdeep_ruby_ext")
end