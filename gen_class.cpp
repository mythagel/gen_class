#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdio>
#include <unistd.h>

std::string git_user_name() {
    std::string user_name;
    if (auto f = popen("git config user.name", "r")) {
        char buf[2048];
        if (fgets(buf, sizeof buf, f)) {
            user_name = buf;
            user_name.erase(user_name.find_last_not_of(" \n\r") + 1);
        }
        pclose(f);
    }
    return user_name;
}

std::string sys_user_login() {
    char buf[2048];
    if (getlogin_r(buf, sizeof buf) == 0)
        return buf;
    return {};
}

int main(int argc, char* argv[]) {
	std::vector<std::string> args(argv, argv + argc);
	if(args.size() < 2) {
		std::cerr << args[0] << " base_name [GPL|MIT]\n"; 
		return 1;
	}
	
	auto class_name = args[1];

    std::string license = "GPL";
    if (args.size() > 2)
        license = args[2];

	auto guard = class_name + "_H_";
	std::transform(guard.begin(), guard.end(), guard.begin(), ::toupper);
	
	std::string create_date;
	{
		auto t = std::time(NULL);
		char buf[256] = {0};
		std::strftime(buf, 256, "%F", std::localtime(&t));
		create_date = buf;
    }

    auto user_name = git_user_name();
    auto user_login = sys_user_login();
	
	if (auto h = std::ofstream(class_name + ".h")) {
        h << "/* Copyright (C) 2016  " << user_name << "\n";
        if (license == "GPL") {
            h << " * \n";
            h << " * This program is free software: you can redistribute it and/or modify\n";
            h << " * it under the terms of the GNU General Public License as published by\n";
            h << " * the Free Software Foundation, either version 3 of the License, or\n";
            h << " * (at your option) any later version.\n";
            h << " * \n";
            h << " * This program is distributed in the hope that it will be useful,\n";
            h << " * but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
            h << " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
            h << " * GNU General Public License for more details.\n";
            h << " * \n";
            h << " * You should have received a copy of the GNU General Public License\n";
            h << " * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n";
        } else if (license == "MIT") {
            h << " * Released under the terms of the MIT license.\n";
        }
        h << " * \n";
        h << " * " << class_name << ".h\n";
        h << " *\n";
        h << " *  Created on: " << create_date << "\n";
        h << " *      Author: " << user_login << "\n";
        h << " */\n";
        h << "\n";
        h << "#ifndef " << guard << "\n";
        h << "#define " << guard << "\n";
        h << "\n";
        h << "#endif /* " << guard << " */";
    }

	if (auto cpp = std::ofstream(class_name + ".cpp")) {
        cpp << "/* Copyright (C) 2016  " << user_name << "\n";
        if (license == "GPL") {
            cpp << " * \n";
            cpp << " * This program is free software: you can redistribute it and/or modify\n";
            cpp << " * it under the terms of the GNU General Public License as published by\n";
            cpp << " * the Free Software Foundation, either version 3 of the License, or\n";
            cpp << " * (at your option) any later version.\n";
            cpp << " * \n";
            cpp << " * This program is distributed in the hope that it will be useful,\n";
            cpp << " * but WITHOUT ANY WARRANTY; without even the implied warranty of\n";
            cpp << " * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n";
            cpp << " * GNU General Public License for more details.\n";
            cpp << " * \n";
            cpp << " * You should have received a copy of the GNU General Public License\n";
            cpp << " * along with this program.  If not, see <http://www.gnu.org/licenses/>.\n";
        } else if (license == "MIT") {
            cpp << " * Released under the terms of the MIT license.\n";
        }
        cpp << " * \n";
        cpp << " * " << class_name << ".cpp\n";
        cpp << " *\n";
        cpp << " *  Created on: " << create_date << "\n";
        cpp << " *      Author: " << user_login << "\n";
        cpp << " */\n";
        cpp << "\n";
        cpp << "#include \"" << class_name << ".h\"\n";
    }
	
	return 0;
}

