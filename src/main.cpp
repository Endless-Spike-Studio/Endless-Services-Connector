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

		CCHttpClient::send(req);
	}
};