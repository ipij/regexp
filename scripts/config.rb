#!/usr/bin/env ruby

File.open("config.ini") do |f|
  f.read.scan(/(.*)\s*=\s*(.*)/).each do |match|
    puts "[#{match[0]}] :: #{match[1]}"
  end
end
