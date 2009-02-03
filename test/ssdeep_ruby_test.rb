require 'test/unit'
require 'pathname'
require Pathname(__FILE__).dirname.parent + "lib/ssdeep"

class SsdeepRubyTest < Test::Unit::TestCase
  def test_fuzzy_hash_exists_for_string
    assert_respond_to(String.new, :fuzzy_hash)
  end

  def test_string_fuzzy_hash
    assert_equal("3:7AUQHL4RH:7EkRH", File.read(Pathname(__FILE__).dirname.parent + "lib/ssdeep.rb").fuzzy_hash)
  end

  def test_fuzzy_hash_exists_for_file
    assert_respond_to(File.new(__FILE__), :fuzzy_hash)
  end

  def test_file_fuzzy_hash
    assert_equal("3:7AUQHL4RH:7EkRH", File.new(Pathname(__FILE__).dirname.parent + "lib/ssdeep.rb").fuzzy_hash)
  end

  def test_fuzzy_compare_exists_for_string
    assert_respond_to(String.new, :fuzzy_compare)
  end

  def test_string_fuzzy_compare
    string1 = 'Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum. Lorem ipsum dolor sit amet, consectetur adipisicing elit, sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.'
    string2 = string1[0..-20]
    assert_operator(string1.fuzzy_compare(string2), :>, 90)
  end
end