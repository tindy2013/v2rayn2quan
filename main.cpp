#include <bits/stdc++.h>
#include <rapidjson/document.h>
//#include <codecvt>
/*
#include <curl_easy.h>
#include <curl_ios.h>
#include <curl_exception.h>
#include <curl/curl.h>


#define BURSIZE 2048
*/

#include <curl/curl.h>

using namespace std;
using namespace rapidjson;

/*
using std::cout;
using std::endl;
using std::ostringstream;

using curl::curl_easy;
using curl::curl_ios;
using curl::curl_easy_exception;
using curl::curlcpp_traceback;
*/

static const std::string base64_chars =
             "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
             "abcdefghijklmnopqrstuvwxyz"
             "0123456789+/";


static inline bool is_base64(unsigned char c) {
  return (isalnum(c) || (c == '+') || (c == '/'));
}

std::string base64_encode(char const* bytes_to_encode, unsigned int in_len) {
  std::string ret;
  int i = 0;
  int j = 0;
  unsigned char char_array_3[3];
  unsigned char char_array_4[4];

  while (in_len--) {
    char_array_3[i++] = *(bytes_to_encode++);
    if (i == 3) {
      char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
      char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
      char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
      char_array_4[3] = char_array_3[2] & 0x3f;

      for(i = 0; (i <4) ; i++)
        ret += base64_chars[char_array_4[i]];
      i = 0;
    }
  }

  if (i)
  {
    for(j = i; j < 3; j++)
      char_array_3[j] = '\0';

    char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
    char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
    char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
    char_array_4[3] = char_array_3[2] & 0x3f;

    for (j = 0; (j < i + 1); j++)
      ret += base64_chars[char_array_4[j]];

    while((i++ < 3))
      ret += '=';

  }

  return ret;

}

std::string base64_decode(std::string const& encoded_string) {
  int in_len = encoded_string.size();
  int i = 0;
  int j = 0;
  int in_ = 0;
  unsigned char char_array_4[4], char_array_3[3];
  std::string ret;

  while (in_len-- && ( encoded_string[in_] != '=') && is_base64(encoded_string[in_])) {
    char_array_4[i++] = encoded_string[in_]; in_++;
    if (i ==4) {
      for (i = 0; i <4; i++)
        char_array_4[i] = base64_chars.find(char_array_4[i]);

      char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
      char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
      char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

      for (i = 0; (i < 3); i++)
        ret += char_array_3[i];
      i = 0;
    }
  }

  if (i) {
    for (j = i; j <4; j++)
      char_array_4[j] = 0;

    for (j = 0; j <4; j++)
      char_array_4[j] = base64_chars.find(char_array_4[j]);

    char_array_3[0] = (char_array_4[0] << 2) + ((char_array_4[1] & 0x30) >> 4);
    char_array_3[1] = ((char_array_4[1] & 0xf) << 4) + ((char_array_4[2] & 0x3c) >> 2);
    char_array_3[2] = ((char_array_4[2] & 0x3) << 6) + char_array_4[3];

    for (j = 0; (j < i - 1); j++) ret += char_array_3[j];
  }

  return ret;
}

vector<string> split(const string &s, const string &seperator){
  vector<string> result;
  typedef string::size_type string_size;
  string_size i = 0;

  while(i != s.size()){
    int flag = 0;
    while(i != s.size() && flag == 0){
      flag = 1;
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[i] == seperator[x]){
            ++i;
            flag = 0;
            break;
        }
    }

    flag = 0;
    string_size j = i;
    while(j != s.size() && flag == 0){
      for(string_size x = 0; x < seperator.size(); ++x)
        if(s[j] == seperator[x]){
            flag = 1;
            break;
        }
      if(flag == 0)
        ++j;
    }
    if(i != j){
      result.push_back(s.substr(i, j-i));
      i = j;
    }
  }
  return result;
}

/*
std::string UnicodeToUTF8(const std::wstring & wstr)
{
    std::string ret;
    try {
        std::wstring_convert< std::codecvt_utf8<wchar_t> > wcv;
        ret = wcv.to_bytes(wstr);
    } catch (const std::exception & e) {
        std::cerr << e.what() << std::endl;
    }
    return ret;
}

unsigned char FromHex(unsigned char x)
{
    unsigned char y;
    if (x >= 'A' && x <= 'Z') y = x - 'A' + 10;
    else if (x >= 'a' && x <= 'z') y = x - 'a' + 10;
    else if (x >= '0' && x <= '9') y = x - '0';
    else assert(0);
    return y;
}
*/
/*
std::string UrlDecode(const std::string& str)
{
    std::string strTemp = "";
    size_t length = str.length();
    for (size_t i = 0; i < length; i++)
    {
        if (str[i] == '+') strTemp += ' ';
        else if (str[i] == '%')
        {
            assert(i + 2 < length);
            unsigned char high = FromHex((unsigned char)str[++i]);
            unsigned char low = FromHex((unsigned char)str[++i]);
            strTemp += high*16 + low;
        }
        else strTemp += str[i];
    }
    return strTemp;
}

int random(int m){
        return rand()%m;
}
*/


/*
string getWebpage(string uri)
{
  ostringstream str;
  string result = "";
  curl_ios<ostringstream> writer(str);
  curl_easy easy(writer);
  easy.add<CURLOPT_URL>(uri.c_str());
  easy.add<CURLOPT_FOLLOWLOCATION>(1L);
  try{
    easy.perform();
  } catch (curl_easy_exception error) {
    curlcpp_traceback errors = error.get_traceback();
    error.print_traceback();
  }
  result = str.str();
  return result;
}
*/

string chkifobfs(string net,string type,string obfs){
  if(type == "none" && net != "ws") return ""; else return obfs;
}

string chkobfs(string net){
  if(net == "ws") return "ws"; else return "http";
}

string chkobfspath(string path){
  if(path != "") return path; else return "/";
}

string chkobfshost(string add,string host){
  if(host == "") return add; else return host;
}

string chktls(string tls){
  if(tls == "tls") return "true"; else return "false";
}

string regexFind(string strSrc,string strFind){
  regex reg;
  smatch result;
  if(regex_search(strSrc.cbegin(),strSrc.cend(),result,regex(strFind))){
    return result[1];
  } else return string();
}

int main(int argc, char* argv[])
{
    //string strRet,strUrl;
    string strInput,strTemp,obfs,quanVmess,strResult;
    string ps,add,port,type,id,net,path,host,tls,ua,method,group;
    //string strArgs;
    //char cmdResult[4096];
    const char *chrTemp=nullptr;
    Document json;
    vector<string> strServers;
    ua="Mozilla/5.0 (iPhone; CPU iPhone OS 12_0 like Mac OS X) AppleWebKit/605.1.15 (KHTML, like Gecko) Mobile/16A5366a";
    group="V2RayProvider";
    method="chacha20-ietf-poly1305";
    //strArgs=argv[1];
    //if(argc<2) return 0;
    //strInput=argv[1];
    cin>>strInput;
    //strCurlOut="curl"+to_string(random(1000))+".tmp";
    //strUrl=UrlDecode(strInput.substr(strInput.find("url=")+4));
    //strInput=getWebpage(strUrl);
    //replace(strUrl.begin(),strUrl.end(),'&','^&');
    //strUrl="curl -O "+strCurlOut+" "+strUrl;
    //system(strUrl.c_str());
    //freopen(strCurlOut.c_str(),"r",stdin);
    //cin>>strInput;
    //fclose(stdin);
    //AccessWeb(strUrl);
    strInput=base64_decode(strInput);
    strServers=split(strInput,"\r\n");
    for(unsigned int i=0;i<strServers.size();i++){
        strTemp=strServers[i].substr(8);
        strTemp=base64_decode(strTemp);
        json.Parse(strTemp.data());
        ps=json["ps"].GetString();
        add=json["add"].GetString();
        port=json["port"].GetString();
        path=json["path"].GetString();
        type=json["type"].GetString();
        id=json["id"].GetString();
        net=json["net"].GetString();
        host=json["host"].GetString();
        tls=json["tls"].GetString();
        obfs=",obfs="+chkobfs(net)+",obfs-path=\""+chkobfspath(path)+"\",obfs-header=\"Host: "+chkobfshost(add,host)+"[Rr][Nn]User-Agent: "+ua+"\"";
        quanVmess=ps+" = vmess,"+add+","+port+","+method+",\""+id+"\",group="+group+",over-tls="+chktls(tls)+",certificate=1"+chkifobfs(net,type,obfs);
        chrTemp=quanVmess.c_str();
        strResult+="vmess://"+base64_encode(chrTemp,quanVmess.size())+'\r';
        //cout<<quanVmess<<endl;
    }
    chrTemp=strResult.c_str();
    cout<<base64_encode(chrTemp,strResult.size())<<endl;
    return 0;
}
