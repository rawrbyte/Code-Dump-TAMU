{-# LANGUAGE NoImplicitPrelude #-}
import Prelude hiding ((>>=))
import Data.Char

type Parser res = String -> [(res, String)]

mySymbolDot :: Parser Char
mySymbolDot []		= []
mySymbolDot (s:ss)	| s == '.' 	= [(s,ss)]
			| otherwise 	=	[]

mySymbol :: Char -> Parser Char
mySymbol c []  = []
mySymbol c (s:ss) 	| s == c 	= [(s,ss)]
			| otherwise 	=	[]

myItem :: Parser Char
myItem = \itm -> case itm of	
		[]	->	[]
		(x:xs)	->	[(x,xs)]

myReturn :: a -> Parser a
myReturn v = \inp -> [(v, inp)]

myFailure :: Parser a
myFailure = (\inp -> [])

myParse :: Parser a -> String -> [(a,String)]
myParse p s = p s

(+++) :: Parser a -> Parser a -> Parser a
p +++ q = \inp -> case p inp of	
			[] -> q inp
			[(v, out)] -> [(v, out)]

{-
(>>=)	:: Parser a -> Parser b -> Parser b
p >>= f = \inp -> case myParse p inp of
			[]	-> []
			[(v, out)]	-> myParse f out 
-}

(>>=)	:: Parser a -> (a -> Parser b) -> Parser b
p >>= f = \inp -> case myParse p inp of
			[]	-> []
			[(v, out)] -> myParse (f v) out 

{- Useful test cases: 
let p = myItem >>= (\v1 -> (mySymbol v1))
let q = myItem >>= (\v1 -> myItem >>= \v2 -> myReturn v2))
 let q' = myItem >>= (\v1 -> myItem >>= \v2 -> myReturn (v1, v2))
-}

testP = 
	myItem 	>>= \v1 ->
	myItem 	>>= \v2 ->
	myItem	>>= \v3 ->
	myReturn $ reverse (v1:v2:v3:[])

evenP = 
	myItem 	>>= \v1 ->
	myItem 	>>= \_ ->
	myItem	>>= \v2 ->
	myReturn (v1:v2:[])

mySat :: (Char -> Bool) -> Parser Char
mySat p = myItem >>= \itm -> if p itm then myReturn itm else (myFailure)

myCharP :: Char -> Parser Char
myCharP x = mySat (== x)
	
myStringParser :: String  -> Parser String
myStringParser []	= myReturn []
myStringParser (x:xs)	=
				(myCharP x) >>= \_ ->
				myStringParser xs >>= \_ ->
				myReturn (x:xs)


myMany :: Parser a -> Parser [a]
myMany p = myMany1 p +++ myReturn [] 

{- What is the difference between these two?
	myReturn []
	myFailure

  What error do we get if we replace "myReturn []" with "[]" above?
-}

myMany1 :: Parser a -> Parser [a]
myMany1 p =
		p >>= \v ->
		(myMany p) >>= \vs ->
		myReturn (v:vs)

myMany' :: Parser a -> Parser [a]
myMany' p = \inp -> case p inp of
			[] -> myReturn [] inp
			[(v,out)] -> [(v:(fst xs), (snd xs))]
   			  where xs = head $ (myMany' (myParse p)) out

floatParse = (myMany (mySat isDigit)) >>= \v ->
		mySymbolDot >>= \_ -> 
		(myMany1 (mySat isDigit)) >>= \v2 ->
		myReturn ("whole num ="++ v++" then after stop = "++v2)

myDigit = (mySat isDigit)

floatParse' = (myMany myDigit) >>= \v ->
		mySymbolDot >>= \_ -> 
		(myMany1 myDigit) >>= \v2 ->
		myReturn ("whole num ="++ v++" then after stop = "++v2)