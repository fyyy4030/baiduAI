#include <iostream>
#include <string>
#include <strings.h>
#include <curl/curl.h>
#include <json/json.h>
#include <stdio.h>
#include "base64.h"
#include "fileOP.h"
#include "getAccessToken.h"
#include "myJson.h"
#include "init.h"
#include "faceDetect.h"
#include "absBusiness.h"
#include "foodDetect.h"
#include "animalDetect.h"
#include "botanyDetect.h"
#include "fdfsUploadFile.h"
#include "mySQL.h"

using namespace std;

int main(int argc, char *argv[])
{
    // 读取文件信息
    Judge judge;
    string fileByte = judge.init(argv[1]);

    //food, 发送 post 请求给百度
    absBusiness* food = new foodDetect;
    int ret = food->discern(judge.m_accessToken, fileByte);
    if (ret != 0)
    {
        cout << "get res err!" << endl;
        return -1;
    }

    // 上传 图片到 fdfs,  fileId 为 fdfs里存储的文件名称
    ret = food->uploadFdfs(argv[1]);
    if (ret != 0)
    {
        delete(food);
        return -1;
    }
   
    // 将图片url, json数据存储到 mysql
    ret = food->saveDB(judge.m_host.data(), judge.m_user.data(), judge.m_passwd.data(), judge.m_dbName.data());
    if (ret != 0)
    {
        //插入数据库失败
        delete(food);
        return -1;
    }
    delete(food);

	return 0;
}
