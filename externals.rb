MxxRu::arch_externals :so5 do |e|
  e.url 'https://sourceforge.net/projects/sobjectizer/files/sobjectizer/SObjectizer%20Core%20v.5.5/so-5.5.20.tar.xz'

  e.map_dir 'dev/so_5' => 'dev'
  e.map_dir 'dev/timertt' => 'dev'
end

MxxRu::git_externals :asio do |e|
  e.url 'https://github.com/chriskohlhoff/asio.git'
  e.commit '9229964dc1853b375077338cb398027a6dbbb148' # Dec 10 2017

  e.map_dir 'asio/include' => 'dev/asio'
end

MxxRu::arch_externals :asio_mxxru do |e|
  e.url 'https://bitbucket.org/sobjectizerteam/asio_mxxru-1.1/get/1.1.2.tar.bz2'

  e.map_dir 'dev/asio_mxxru' => 'dev'
end

MxxRu::arch_externals :nodejs_http_parser do |e|
  e.url 'https://github.com/nodejs/http-parser/archive/v2.7.1.tar.gz'

  e.map_file 'http_parser.h' => 'dev/nodejs/http_parser/*'
  e.map_file 'http_parser.c' => 'dev/nodejs/http_parser/*'
end

MxxRu::arch_externals :nodejs_http_parser_mxxru do |e|
  e.url 'https://bitbucket.org/sobjectizerteam/nodejs_http_parser_mxxru-0.1/get/v.0.1.0.tar.bz2'

  e.map_dir 'dev/nodejs/http_parser_mxxru' => 'dev/nodejs'
end

MxxRu::arch_externals :fmt do |e|
  e.url 'https://github.com/fmtlib/fmt/archive/4.0.0.zip'

  e.map_dir 'fmt' => 'dev/fmt'
end

MxxRu::arch_externals :fmtlib_mxxru do |e|
  e.url 'https://bitbucket.org/sobjectizerteam/fmtlib_mxxru-0.1/get/v.0.1.0.tar.bz2'

  e.map_dir 'dev/fmt_mxxru' => 'dev'
end

MxxRu::arch_externals :rapidjson do |e|
  e.url 'https://github.com/miloyip/rapidjson/archive/v1.1.0.zip'

  e.map_dir 'include/rapidjson' => 'dev/rapidjson/include'
end

MxxRu::arch_externals :rapidjson_mxxru do |e|
  e.url 'https://bitbucket.org/sobjectizerteam/rapidjson_mxxru-1.0/get/v.1.0.0.tar.bz2'

  e.map_dir 'dev/rapidjson_mxxru' => 'dev'
end

MxxRu::arch_externals :json_dto do |e|
  e.url 'https://bitbucket.org/sobjectizerteam/json_dto-0.2/downloads/json_dto-0.2.3-full.zip'

  e.map_dir 'dev/json_dto' => 'dev'
end

MxxRu::arch_externals :args do |e|
  e.url 'https://github.com/Taywee/args/archive/6.2.0.zip'

  e.map_file 'args.hxx' => 'dev/args/*'
end

MxxRu::arch_externals :catch do |e|
  e.url 'https://github.com/catchorg/Catch2/archive/v2.0.1.zip'

  e.map_file 'single_include/catch.hpp' => 'dev/catch/*'
end
