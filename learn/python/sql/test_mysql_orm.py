#!/usr/bin/env python
# coding=utf-8
# by orientlu
# pip3 install sqlalchemy

#import pymysql
from sqlalchemy import Column, String, create_engine
from sqlalchemy.orm import sessionmaker
from sqlalchemy.ext.declarative import declarative_base


Base = declarative_base()

## table row --> class object
class User(Base):
    __tablename__= 'user'

    # table struct
    id = Column(String(20), primary_key=True)
    name = Column(String(20))

## open db, user module pymysql
engine = create_engine('mysql+pymysql://root:jklfds@localhost:3306/testdb')
#engine = create_engine('mysql+mysqlconnector://root:jklfds@localhost:3306/testdb')
DBSession = sessionmaker(bind=engine)

session = DBSession()
new_user = User(id='7', name='lcd')
session.add(new_user)
session.commit()
user = session.query(User).filter(User.id=='2').one()
print(user.id, user.name)

users = session.query(User).all()
for user in users:
    print(user.id, user.name)

session.close()

