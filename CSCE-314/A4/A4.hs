-- CSCE 314 Homework Assignment  #4 // 304-501 // Raymond Zhu // 923008555
import Parsing
import Data.Char

sat1:: ([Char] -> Bool) -> Parser String
sat1 p =  do x <- (many item)
             if p x then return x else failure

doc0 = "<head></head><body></body>" -- valid
doc1 = " <head> Test1 </head> <body> Testing <p> Test <b> bold </b> text. <ol> <li> test item <li> another one </ol> </body>" -- valid
doc2 = "<head> Test2 <body> Testing </body>" -- invalid
doc3 = "<head> Test3 </head> <body> <a href=\"test.doc\">hyperlink <i> text </a> </i> </body>" -- invalid
doc4 = "<b> <i> <b> blah</b> </i> </b>" -- invalid
doc5 = " <head> ahelaswad </head> <body> babab <b> <i> ada</i> </b> c </body>" -- valid
doc6 = " <head> ahelaswad </head> <body> babab <b> </i> ada</i> </b> c </body>" -- invalid
doc7 = " <head> ahelaswad </head> <body> babab <b> <b> ada</b> </b> c </body>" -- invalid--------------------
doc8 = " <head> ahelaswad </head> <body> babab <a href=\"\"> </a> </body>" -- valid
doc9 = " <head> ahelaswad </head> <body> babab <a href=\"hello.txt\"> </a> </body>" -- valid
doc10 = " <head> ahelaswad </head> <body> babab <a href=\"hello.txt\"> <b> bold </b> </a> </body>" -- valid
doc11 = " <head> ahelaswad </head> <body> babab <b> <a href=\"hello.txt\"> <b> bold </b> </a> </b> </body>" -- invalid---------
doc12 = " <head> ahelaswad </head> <body> babab <i> <a href=\"hello.txt\"> <b> bold </b> </a> </i> </body>" -- valid
doc13 = " <head> ahelaswad </head> <body> babab <li> </body>" -- invalid
doc14 = " <head> ahelaswad </head> <body> <b> hel </b> <a href=\"hello\"> hell </a> </body>" -- valid
doc15 = " <head> ahelaswad </head> <body> babab <ul><li> </ul> </body>" -- valid
doc16 = " <head> ahelaswad </head> <body> babab <ul><li> </ol> </body>" -- invalid
doc17 = " <head> ahelaswad </head> <body> babab <ul><li> <li> </ul> </body>" -- valid
doc18 = " <head> ahelaswad </head> <body> babab <ul><li> <li> </ul> <li> </body>" -- invalid
doc19 = " <head> ahelaswad </head> <body> babab <ul><li> <li> </ul> <ol><li></ol> </body>" -- valid

eatWhiteSpace [] = []
eatWhiteSpace (x:xs) = if or[(x=='.'),(x=='?'),(x=='!')] then eatWhiteSpace xs else x:(eatWhiteSpace xs)

listTag::Parser Bool
listTag =  do symbol "<b>"
              many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
              listTag 
              many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
              symbol "</b>"
              return True
              +++ do symbol "<i>"
                     many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                     listTag
                     many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                     symbol "</i>"
                     return True
                     +++ do symbol "<p>"
                            many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                            listTag
                            return True
                            +++ do symbol "<br>"
                                   many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                   listTag
                                   return True
                                   +++ do symbol "<a href="
                                          char '"'
                                          many (alphanum +++ (char '.') +++ (char '?') +++ (char '!'))
                                          char '"'
                                          char '>'
                                          listTag
                                          symbol "</a>"
                                          return True
                                          +++ do symbol "<li>"
                                                 many (alphanum +++ (sat isSpace))  
                                                 listTag
                                                 return True
                                                 +++ do symbol "<ul>"
                                                        many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                        listTag
                                                        many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                        return True
                                                        +++ do many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                               return True +++ return False

bitalTag::Parser Bool
bitalTag = do symbol "<p>"
              many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
              italTag
              return True
              +++ do symbol "<br>"
                     many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                     italTag
                     return True
                     +++ do symbol "<a href="
                            char '"'
                            many (alphanum +++ (char '.') +++ (char '?') +++ (char '!'))
                            char '"'
                            char '>'
                            italTag
                            symbol "</a>"
                            italTag
                            return True
                            +++ do symbol "<ol>"
                                   many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                   listTag
                                   many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                   symbol "</ol>"
                                   italTag
                                   return True
                                   +++ do symbol "<ul>"
                                          many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                          listTag
                                          many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                          symbol "</ul>"
                                          italTag
                                          return True
                                          +++ do many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                 return True +++ return False

italTag::Parser Bool
italTag = do symbol "<b>"
             many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
             bitalTag
             many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
             symbol "</b>"
             italTag
             return True
             +++ do symbol "<p>"
                    many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                    italTag
                    return True
                    +++  do symbol "<br>"
                            many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                            italTag
                            return True
                            +++ do symbol "<a href="
                                   char '"'
                                   many (alphanum +++ (char '.') +++ (char '?') +++ (char '!'))
                                   char '"'
                                   char '>'
                                   italTag
                                   symbol "</a>"
                                   italTag
                                   return True
                                   +++ do symbol "<ol>"
                                          many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                          listTag
                                          many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                          symbol "</ol>"
                                          italTag
                                          return True
                                          +++ do symbol "<ul>"
                                                 many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                 listTag
                                                 many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                 symbol "</ul>"
                                                 italTag
                                                 return True
                                                 +++ do many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                        return True +++ return False

boldTag::Parser Bool
boldTag = do symbol "<i>"
             many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
             bitalTag
             many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
             symbol "</i>"
             boldTag
             return True
             +++  do symbol "<p>"
                     many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                     boldTag
                     return True
                     +++ do symbol "<br>"
                            many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                            boldTag
                            return True
                            +++ do symbol "<a href="
                                   char '"'
                                   many (alphanum +++ (char '.') +++ (char '?') +++ (char '!'))
                                   char '"'
                                   char '>'
                                   boldTag
                                   symbol "</a>"
                                   boldTag
                                   return True
                                   +++ do symbol "<ol>"
                                          many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                          listTag
                                          many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                          symbol "</ol>"
                                          boldTag
                                          return True
                                          +++ do symbol "<ul>"
                                                 many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                 listTag
                                                 many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                 symbol "</ul>"
                                                 boldTag
                                                 return True
                                                 +++ do many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!')) 
                                                        return True +++ return False

otherTag::Parser Bool
otherTag = do symbol "<b>"
              many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
              boldTag 
              many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
              symbol "</b>"
              otherTag
              return True
              +++ do symbol "<i>"
                     many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                     italTag
                     many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                     symbol "</i>"
                     otherTag
                     return True
                     +++ do symbol "<p>"
                            many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                            otherTag
                            return True
                            +++ do symbol "<br>"
                                   many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                   otherTag
                                   return True
                                   +++ do symbol "<a href="
                                          char '"'
                                          many (alphanum +++ (char '.') +++ (char '?') +++ (char '!'))
                                          char '"'
                                          char '>'
                                          otherTag
                                          symbol "</a>"
                                          otherTag
                                          return True
                                          +++ do symbol "<ol>"
                                                 many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!')) 
                                                 listTag
                                                 many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                 symbol "</ol>"
                                                 otherTag
                                                 return True
                                                 +++ do symbol "<ul>"
                                                        many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                        listTag
                                                        many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                        symbol "</ul>"
                                                        otherTag
                                                        return True
                                                        +++ do many (alphanum +++ (sat isSpace) +++ (char '.') +++ (char '?') +++ (char '!'))
                                                               return True +++ return False
 
html::Parser Bool
html = do symbol "<head>"
          many (alphanum +++ (sat isSpace))
          symbol "</head>"
          space
          symbol "<body>"
          otherTag
          otherTag
          otherTag
          otherTag
          otherTag
          otherTag
          otherTag
          otherTag
          symbol "</body>"
          return True
          +++ return False

eval1   :: String -> [(Bool,String)]
eval1 xs = parse html (xs)
-------------------------------------------------------------------Polynomial Part----------------------------------------------------------------------------------------------------------------------------------------------------------
getInt :: IO Int
getInt = do
  s <- getLine
  return (read s)
  
getFloat :: IO Float
getFloat = do line <- getLine
              return (read line:: Float) 

printStringNTimes 0 a = do
  putStrLn ("What is the x^0 coefficient")
  num <- getFloat
  return (num:a)
 
  
printStringNTimes n a =
 do
  putStrLn ("What is the x^" ++ (show n) ++ " coefficient")
  num <- getFloat  
  printStringNTimes (n-1) (num:a)

evalpoly = do
	putStrLn "What is the degree of the polynomial"
	num <- getInt
	a <- printStringNTimes num []
	putStrLn "What value do you want to evaluate at: "
	num2 <- getFloat
	let b =	take2lists (trial num) a num2
	putStrLn ("The value of " ++ (pry num (reverse a))++(printing (num -1) (tail(reverse a))) ++ " at " ++ (show num2) ++ " is " ++ show(sum(b)))
	
trial x = [0..x]

take2lists [] [] a = []
take2lists (x:xs) (y:ys) a = ((a^x)*y ):(take2lists xs ys a)
	
printing 0 [] = ""
printing 0 (x:xs) = if (x == 0)
					then ("")
					else
						if ( x > 0)
						then ("+" ++ show(x)) 
						else (show(x))
printing a (x:xs) = if(x == 0)
				    then ("")++(printing (a-1) xs)
					else 
						if (x > 0)
						then("+" ++ (show(x))++ "x^" ++ (show a) ++ (printing (a-1) xs))
						else("+" ++ (show(x))++ "x^" ++ (show a) ++ (printing (a-1) xs))

pry a (x:xs) = show(x) ++ "x^" ++ show(a)