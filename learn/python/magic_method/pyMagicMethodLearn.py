#!/usr/bin/env python
# coding=utf-8

import collections
from random import choice

Card = collections.namedtuple('Card', ['rank', 'suit'])

class FrenchDeck:
    ranks = [str(n) for n in range(2, 11)] + list('JQKA')
    suits = 'spades diamonds clubs hearts'.split()

    def __init__(self):
        print("ranks" + str(self.ranks))
        print("suits" + str(self.suits))
        self._Cards = [Card(rank, suit) for suit in self.suits
                                        for rank in self.ranks]

    def __len__(self):
        print("__len__ called")
        return len(self._Cards)

    def __getitem__(self, position):
        print("__getitem__ called")
        return self._Cards[position]

def spades_high(card):
    suit_valuse = dict(spades=3, hearts=2, diamonds=1, clubs=0)
    rank_value = FrenchDeck.ranks.index(card.rank)
    return rank_value * len(suit_valuse) + suit_valuse[card.suit]

if __name__ == '__main__':
    deck = FrenchDeck()
    print(len(deck))
    print(deck[0])
    print(deck[-1])

    # get one item from list randomly
    print(choice(deck))
    print(choice(deck))

    print("get item 0, 1, 2")
    print(deck[:3])
    print('get item 12 - all, step 13')
    print(deck[12::13])

    print('iteration')
    for card in deck:
        print(card)

    print('iteration reversed')
    for card in reversed(deck):
        print(card)

    print('sort')
    for card in sorted(deck, key=spades_high) :
        print(card)

