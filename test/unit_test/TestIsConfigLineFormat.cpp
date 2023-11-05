#include <string>
#include "gtest/gtest.h"
#include "Config.hpp"
#include "IsConfigFormat.hpp"
#include "HandlingString.hpp"

TEST(IsConfigLineTest, IsStartLocationBlock)
{
	std::string	location_path;

	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location aaa {", &location_path));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location aaa          {", &location_path));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location aa {	   ", &location_path));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("      location a {	   ", &location_path));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("      location 		any	{	   ", &location_path));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("    location / {", &location_path));
	// arg : const std::string &config_line
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location / {"));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location /\t{"));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block(" location \t/\t { \t"));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location location {"));

	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location", &location_path));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("locat", &location_path));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location{{", &location_path));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("      location{	   {", &location_path));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("      loca tion  {", &location_path));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("", &location_path));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("aaaa", &location_path));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("locationaaa{", &location_path));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("      location a{	   ", &location_path));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("      location 		any	{	   {", &location_path));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block(""));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block(" "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location { {")); // KO
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location {{{ {")); // KO
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location { { { {"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location \v {")); // KO
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location{"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("{"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("}"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location a b c {"));
	// arg : const std::string &config_line, std::string *config_location_path
	location_path = "printable_path";
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location / {", &location_path));
	location_path = "aaa 123";
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_location_block("location / {", &location_path));
	location_path = "";
	EXPECT_FALSE(IsConfigFormat::is_start_location_block("location / {", &location_path)); // KO
	location_path = "\t\r\n";
	EXPECT_FALSE(IsConfigFormat::is_start_location_block("location / {", &location_path));
}

TEST(IsConfigLineTest, IsLocationBlockFormatFormat)
{
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("key val; "));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("	 key val    val     val;          "));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format(" key val    val     val          val;"));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("	 key val    val   	 val;"));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("  key val    val   	 val;    "));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("		key value;"));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("a b;"));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format(" a b;"));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format(" a b;     "));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("\ta\tb;\t\t\t"));
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("\" \";"));

	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("keyval;"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("key			val "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format(""));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("	 key "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("  key ; "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("  }; "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("  		} a aaaa aaaa "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("key val; ;"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("keyval;"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("key			val "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format(""));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("	 key "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("  key ; "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("  }; "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("  		} a aaaa aaaa "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("key val; ;"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("a b ;"));  // KO
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("a b\t;"));  // KO
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format(";"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format(" ; "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("; ;"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("; ; ;"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("{ };"));  // KO
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("} {;"));  // KO
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("        "));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format(" \r \r;")); // KO
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format(" \v \v;")); // KO
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format(""));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("a;"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("a; ;"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("a b;\r;"));
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_location_block_format("key val ; "));
}

TEST(IsConfigLineTest, IsStartServerBlock)
{
	bool test_bool;

	test_bool = false;
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server {", &test_bool));
	EXPECT_TRUE(test_bool);

	test_bool = false;
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("	server {	", &test_bool));
	EXPECT_TRUE(test_bool);

	test_bool = false;
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server		{	", &test_bool));
	EXPECT_TRUE(test_bool);

	test_bool = false;
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("      server 		 {		   ", &test_bool));
	EXPECT_TRUE(test_bool);

	test_bool = false;
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server {", &test_bool));
	EXPECT_TRUE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server{", &test_bool)); // KO
	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block(" server{     ", &test_bool)); // KO

	test_bool = false;
	EXPECT_EQ(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("\tserver\t{\t \t", &test_bool));
	EXPECT_TRUE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server {{", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server { {", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server { server {", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server server {", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("{ server {", &test_bool));
	EXPECT_FALSE(test_bool);


	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("      ", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("{", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("s", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server {{", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("      server {	   {", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("serve {", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("{", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server aaa {", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("server{", &test_bool));
	EXPECT_FALSE(test_bool);

	test_bool = false;
	EXPECT_NE(CONFIG_FORMAT_OK, IsConfigFormat::is_start_server_block("     server{", &test_bool));
	EXPECT_FALSE(test_bool);
}