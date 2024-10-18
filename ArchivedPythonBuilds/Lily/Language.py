from dataclasses import dataclass

class Type:
    def __init__(self, Object):
        self.Object = Object

    def Cast(self, Type):
        Type(self.Object.Value) 

@dataclass
class Integer(Type):
    DelcarativeName: str
    Value: int


@dataclass
class String(Type):
    DelcarativeName: str
    Value: str


@dataclass
class List(Type):
    DelcarativeName: str
    Value: list

Types = {"Integer": Integer,
         "String": String,
         "List": List,}

Constructs = {"[": "ArrayOpen",
              "]": "ArrayClose",
              "{": "BlockOpen",
              "}": "BlockClose",
              ";": "StatementEnd"}