#include <Geode/modify/CCHttpClient.hpp>

using namespace geode::prelude;

std::string replace(std::string haystack, std::string needle, std::string replacement) {
    std::size_t index = haystack.find(needle);

    if (std::string::npos != index) {
        return haystack.replace(index, needle.length(), replacement);
    }

    return haystack;
}

class $modify(CCHttpClient) {
	void send(CCHttpRequest* req)
    {
		std::string url = req->getUrl();

        std::string service = Mod::get()->getSettingValue<std::string>("service");

        std::string old_server_host = "www.boomlings.com/database";

        if (service == "Endless Proxy") {
            std::string endless_proxy_url = "https://endless-services.zhazha120.cn/api/EndlessProxy/GeometryDash";
            url = replace(url, "http://" + old_server_host, endless_proxy_url);
            url = replace(url, "https://" + old_server_host, endless_proxy_url);
        }

        if (service == "Endless Server") {
            std::string endless_server_url = "https://endless-services.zhazha120.cn/api/EndlessServer/GeometryDash";
            url = replace(url, "http://" + old_server_host, endless_server_url);
            url = replace(url, "https://" + old_server_host, endless_server_url);
        }

        const char* final_url = url.c_str();
	    req->setUrl(final_url);

        #ifndef GEODE_IS_ANDROID
        bool debug = Mod::get()->getSettingValue<bool>("debug");

        if (debug) {
            cocos2d::extension::CCHttpRequest::HttpRequestType d_rt = req->getRequestType();

            std::string d_method = "UNKNOWN";

            if (d_rt == cocos2d::extension::CCHttpRequest::HttpRequestType::kHttpGet) {
                d_method = "GET";
            }

            if (d_rt == cocos2d::extension::CCHttpRequest::HttpRequestType::kHttpPost) {
                d_method = "POST";
            }

            if (d_rt == cocos2d::extension::CCHttpRequest::HttpRequestType::kHttpPut) {
                d_method = "PUT";
            }

            if (d_rt == cocos2d::extension::CCHttpRequest::HttpRequestType::kHttpDelete) {
                d_method = "DELETE";
            }

            std::string d_url = req->getUrl();
            log::info("{} {}", d_method, d_url);

            std::vector<std::string> d_headers = req->getHeaders();

            for(std::vector<std::string>::iterator header = d_headers.begin(); header != d_headers.end(); header++)
            {
                log::info("{}", *header);
            }

            std::string d_data = req->getRequestData();

            log::info("{}", d_data);
        }
        #endif

        CCHttpClient::send(req);
    }
};