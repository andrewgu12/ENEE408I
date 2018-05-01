from __future__ import print_function
import boto3
from boto3.dynamodb.conditions import Key, Attr
import json
from helpers import build_response, build_speechlet_response

dynamodb = boto3.resource('dynamodb', region_name='us-east-1')
table = dynamodb.Table('Locations')

def add():
  with open('locations.json') as json_file:
    locations = json.load(json_file)  
    for location in locations['locationObjects']:
      table.put_item(
        Item={
          'id': location['id'],
          'location': location['location'],
          'value': location['value']
        }
      )
  
  return build_response({}, build_speechlet_response("Hello", "succesfully added items to DB", None, False))

def find_room(room):
  response = table.query(
    KeyConditionExpression=Key('location').eq(room)
  )

  returnLocation = None
  if response['Count'] > 0:
    item = response['Items'][0]
    returnLocation = item['value']
  return returnLocation