//
// Created by swql on 12/19/20.
//

#include "logger.h"

void logger::handle_provided_path(std::filesystem::path &path, std::string* optional_name) {
    {
        try{
            if (!std::filesystem::exists(path)) {
                std::filesystem::create_directory(path);
            }
            else if (!std::filesystem::is_directory(path)){
                throw std::runtime_error("Provided path is not a directory");
            }
            create_new_log_file(path, optional_name);
        }
        catch (std::runtime_error& err){
            std::cout << "[Logger error on init]: " << err.what() << std::endl;
        }

    }
}

void logger::create_new_log_file(std::filesystem::path &path, std::string* optional_name) {

    // User defined file name case
    if (optional_name){
        path.append(*optional_name);
    }

    // Default file name case
    else{
        auto datetime = get_timestamp(true);
        path.append("log" + datetime + ".txt");
    }

    this->handle.open(path);
    if (!this->handle.good()) { throw std::runtime_error("Error while creating file"); }
}

logger::logger(std::filesystem::path& path)
{
    initialize(path);
}

logger::logger() {
    std::filesystem::path path {"./"};
    initialize(path);
}

std::string logger::get_timestamp(bool spacefree) {
    time_t time = std::time(NULL);
    tm* tm_struct = std::localtime(&time);
    std::string datetime(std::asctime(tm_struct));
    datetime.pop_back();
    if (spacefree) {
        // Remove-erase idiom
        std::replace(datetime.begin(), datetime.end(), ' ', '-');
    }
    return datetime;
}

void logger::initialize(std::filesystem::path &path, std::string* optional_name) {
    {
        try{
            handle_provided_path(path, optional_name);
        }
        catch (std::runtime_error& err){
            std::cout << "Logger failed to create/use a directory path provided by: " << path
                      << std::endl;
        }
    }
}

logger::logger(const char *path) {
    std::filesystem::path p {path};
    initialize(p);
}

logger::logger(std::string &path) {
    std::filesystem::path p {path};
    initialize(p);
}

logger::logger(std::filesystem::path &path, std::string &name) {
    initialize(path, &name);
}

logger::logger(std::string &path, std::string& name) {
    std::filesystem::path p {path};
    initialize(p, &name);
}

logger::logger(const char *path, std::string &name) {
    std::filesystem::path p {path};
    initialize(p, &name);
}
