import boto3


def delete_movie_table(dynamodb=None):
    if not dynamodb:
        dynamodb = boto3.resource('dynamodb', region_name='ap-southeast-1')

    table = dynamodb.Table('Music')
    table.delete()


if __name__ == '__main__':
    delete_movie_table()
    print("Music table deleted.")