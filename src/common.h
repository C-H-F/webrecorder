#pragma once

#include "libs/nonstd/span.hpp"
#include "libs/SimpleWeb/utility.hpp"

using StatusCode = SimpleWeb::StatusCode;
using Header = SimpleWeb::CaseInsensitiveMultimap;
using ByteVector = std::vector<std::byte>;
using ByteView = nonstd::span<const std::byte>;
using StringViewPair = std::pair<std::string_view, std::string_view>;

struct LStringView : std::string_view {
  LStringView(std::string_view s) : std::string_view(s) { }
  LStringView(const char* s) : std::string_view(s) { }
  LStringView(const std::string& s) : std::string_view(s) { }
  LStringView(std::string&& s) = delete;
};

std::string format_time(time_t time);
time_t parse_time(const std::string& string);
const std::string& to_string(StatusCode status_code);
bool starts_with(std::string_view str, std::string_view with);
bool ends_with(std::string_view str, std::string_view with);
std::string_view trim(LStringView str);
std::string_view unquote(LStringView str);
void replace_all(std::string& data, const std::string& search, const std::string& replace);
ByteView as_byte_view(std::string_view data);
std::string_view as_string_view(ByteView data);
bool iequals(std::string_view s1, std::string_view s2);
template<typename T, typename... S>
bool iequals_any(T&& a, S&&... b) {
  return (iequals(a, b) || ...);
}

StringViewPair split_content_type(std::string_view content_type);
std::string get_content_type(std::string_view mime_type, std::string_view charset);

std::string get_hash(ByteView in);
std::string get_legal_filename(const std::string& filename);
std::string to_local_filename(std::string url, size_t max_length = 255);
std::string filename_from_url(const std::string& url);
std::string url_from_input(const std::string& url_string);

bool is_relative_url(std::string_view url);
bool is_same_url(std::string_view a, std::string_view b);
std::string to_absolute_url(std::string_view url, const std::string& relative_to);
std::string_view to_relative_url(LStringView url, std::string_view base_url);
std::string_view get_scheme(LStringView url);
std::string_view get_hostname(LStringView url);
std::string_view get_hostname_port(LStringView url);
std::string_view get_scheme_hostname_port(LStringView url);
std::string_view get_scheme_hostname_port_path(LStringView url);
std::string_view get_scheme_hostname_port_path_base(LStringView url);
std::string_view get_without_first_domain(LStringView url);
std::string_view get_file_extension(LStringView url);
