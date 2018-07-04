#!/usr/bin/ruby

INT_MAX=`getconf INT_MAX`.to_i
src_size=ARGV[0].to_i

if (src_size == 0)
	STDERR.puts("usage: [num of samples]",
		    "example: #{$0} 30_000_000");
	exit(1);
end

File.open("nums.dat", File::TRUNC|File::RDWR|File::CREAT, 0644) { |f|

	src_size.times {
		f.puts(Random.rand(INT_MAX));
	}

}
