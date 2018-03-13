#include <iostream>
#include <string>
#include <strings.h>
#include <curl/curl.h>
#include <json/json.h>
#include "base64.h"
#include "fileOP.h"
#include "getAccessToken.h"
#include "myJson.h"
#include "init.h"
#include "faceDetect.h"
#include "absBusiness.h"
#include "foodDetect.h"

using namespace std;

int main(int argc, char *argv[])
{
    // 读取文件信息
    Judge judge;
    string fileByte = judge.init(argv[1]);

    // 获取 access
    string accessToken;
    getAccessToken *access = getAccessToken::getInstance();
    access->get_access_token(accessToken, getAccessToken::API_Key, getAccessToken::Secure_Key);

    /* face
    absBusiness* face = new faceDetect;
    int ret = face->discern(accessToken, fileByte);
    */

    // food
    absBusiness* food = new foodDetect;
    int ret = food->discern(accessToken, fileByte);
    if (ret != 0)
    {
        cout << "get res err!" << endl;
        return -1;
    }

    Json::Value res = food->resJson();

    cout << res << endl;
    
    //delete(face);
    delete(food);
    
    return 0;
}
