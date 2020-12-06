import boto3
import uuid
from botocore.exceptions import ClientError

session = boto3.Session(profile_name='bob9df')
s3client = session.client('s3')
bucket_name = 'bob9-pd-6112-presigned'
print('creating new bucket with with name: {}'.format(bucket_name))
s3client.create_bucket(Bucket=bucket_name)

list_buckets_resp = s3client.list_buckets()
for bucket in list_buckets_resp['Buckets']:
    if bucket['Name'] == bucket_name:
        print('(Just created) -> {} - there since {}'.format(bucket['Name'], bucket['CreationDate']))
object_key = 'presigned-handson-6112.txt'

print('Uploading some data to {} with key: {}'.format(bucket_name, object_key))
s3client.put_object(Bucket=bucket_name, Key=object_key, Body=b'KITRI BOB 9th!')

url = s3client.generate_presigned_url(
    ClientMethod='get_object',
    Params={
        'Bucket':bucket_name,
        'Key':object_key
        })
print('\nTry this URL in your browser to download the object:')
print(url)

try:
    input = raw_input
except NameError:
    pass
input("\nPress enter to continue....")
