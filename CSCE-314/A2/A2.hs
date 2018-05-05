-- CSCE 314 Homework Assignment  #2 // 304-501 // Raymond Zhu // 923008555
import Data.Char	(isAlpha, isLower, isUpper, toLower, isDigit, isHexDigit, isOctDigit, isSpace, ord, chr, digitToInt)
-- Chinese Remainder Theorem -- 
crt :: [(Integer,Integer)] -> (Integer,Integer)
crt xs 
		| length xs == 1 		= error "Need at least two Tuples"
		| otherwise 			= (head(equivList(allLists((makeprodMods xs), xs))),prodMods(xs))

--End of list number
prodMods :: [(Integer,Integer)] -> Integer
prodMods xs
		| xs == [] 		= 1
		| otherwise 	= (snd(head(xs)))*(prodMods(tail(xs)))

makeprodMods xs = [1..prodMods(xs)]	

--Finds the values that fit the requirement of the list		
modListTwo (a,n,xs)
		|  xs == [] = []
		| (head(xs)) `mod` n == a 	= (head(xs)):(modListTwo(a,n,tail(xs)))
		| (head(xs)) `mod` n /= a  	= (modListTwo(a,n,tail(xs)))

--Makes a list of lists	
allLists (axs,fxs)
		| fxs == [] 	= []
		|otherwise 	= modListTwo(fst(head(fxs)),snd(head(fxs)),axs) : allLists(axs,(tail(fxs)))

--Checks for the intersecting number from the list of lists
equivList :: [[Integer]] -> [Integer]
equivList (a:b:xs)
		| length xs == 0 		= compList(a,b)
		| otherwise 			= compList (a,equivList(b:xs))

--Compares a list with a list in a list of lists
compList ((x:axs),bxs) =
				if length(x:axs) == 2
					then 
						if (findElement x bxs)
							then x : (compList(axs,bxs))
						else compList(axs,bxs)
					else
				if length(x:axs) == 1
					then 
					if (findElement x bxs)
						then [x]
					else []
				else
					if (findElement x bxs)
						then x :(compList(axs,bxs))
					else compList(axs,bxs)

findElement x [] = False
findElement x (y:xs)
		| x == y 		= True 
		| otherwise 	= findElement x xs
					 
-- k-composite --
kcomposite :: Integral t => Int -> [t]
kcomposite 0 = []
kcomposite k = map fromIntegral (composite k k)

-- Checks whether number is a k-composite --
composite :: Int -> Int -> [Int]
composite x y
		| length(drop 1 (remove x x)) == y 		= [x] ++ (composite (incr1 x) y)
		| otherwise 									= composite (incr1 x) y
		where i = 1
incr1 x = x+1
		
-- Finds all factors of given number and stores them in a list -- 
remove :: Int -> Int -> [Int]
remove x y
		| y == i = []
		| mod x (i `subtract` y) == 0 		= [(i `subtract` y)] ++ remove x (i `subtract` y)
		| otherwise 								= remove x (i `subtract` y)
		where i = 1

-- A simple anagram code -- 
anagramEncode :: [Char] -> [Char]
anagramEncode [] 		= []
anagramEncode x 		= concatMatrix ( ( splitSecret ( modifySecret x ) ( modifySecret x ) ) )

-- Finds the nearest k-composite number greater than the length of chars -- 
compositeSize :: [Char] -> [Int] -> Int
compositeSize ls xs
		| length ls > head xs 	= compositeSize ls (tail xs)
		| otherwise 				= head xs

-- Modifies char list and replaces blanks with X -- 
modifySecret :: [Char] -> [Char]
modifySecret ls
		| length ls < compositeSize ls (kcomposite 2) 	= modifySecret(reverse('X':reverse(ls)))
		| otherwise 												= ls		
		
-- Splits list of chars into rows based on smallest factor -- 		
splitSecret :: [Char] -> [Char] -> [[Char]]
splitSecret ls ys
		| ls == [] = []
		| length ls >= head(remove (length ys) (length ys)) 
			= [ take (head(remove (length ys) (length ys))) ls ] 
			++ (splitSecret ((drop (head(remove (length ys) (length ys)))) ls) ys) 
		| otherwise = []

-- Combines a list of lists into a single list -- 
concatMatrix :: [[Char]] -> [Char]
concatMatrix ls 
		| length (head ls) >= 1 	= combineMap(map (take 1) ls) ++ (concatMatrix (map (drop 1) ls))
		| otherwise 					= []

-- Helper function for concatMatrix -- 
combineMap ls 
		| ls /= [] 		= head(head ls):combineMap(drop 1 ls)
		| otherwise 	= []
		
-- Decodes anagram -- 
anagramDecode :: [Char] -> [Char]
anagramDecode [] 	= []
anagramDecode x 	= removeX(concatMatrix(splitCrypted x x))	

-- Removes the padded X at the end of list --
removeX :: [Char] -> [Char]
removeX (x:xs)
		| xs == [] 			= []
		| last xs == 'X' 	= removeX (x:init xs)
		| otherwise 		= x:xs
		
-- Splits code into lists based on row factor --	
splitCrypted :: [Char] -> [Char] -> [[Char]]
splitCrypted x y
		| length x >= head(tail(remove(length y) (length y))) 
			= [take (head(tail(remove(length y) (length y)))) x] 
			++ splitCrypted (drop (head(tail(remove(length y) (length y)))) x) y 
		| otherwise = []

-- Set Constructor -- 
type Set a = [a]
isElement :: Eq a => a -> [a] -> Bool
isElement x [] = False
isElement x (y:xs) = if x == y then True else isElement x xs

mkSet :: Eq a => [a] -> Set a
mkSet [] 		= []
mkSet (x:[]) 	= [x]
mkSet (x:xs)	= if (isElement x xs) then (mkSet xs) else (x:(mkSet xs))		
	
-- Set Subset -- 
subset :: Eq a => Set a -> Set a -> Bool
subset [] _ = True
subset x y
		| (compList(x,y) == x) 		= True
		| otherwise 					= False

-- Set Equality -- 
setEqual :: Eq a => Set a -> Set a -> Bool
setEqual x y = if length(x) == 1 && length(y) == 1
			   then
				   if head(x) == head(y)
				   then True
				   else False
			   else
				   if (subset x y) == (subset y x)
				   then True
				   else False

-- Set Product --	
setProd :: (Eq t, Eq t1) => Set t -> Set t1 -> Set (t, t1)
setProd (x:xs) (y:ys) = combineSet (x:xs) (y:ys) ++ setProd (xs) (y:ys)
setProd [] (y:ys) 	= []
setProd (x:xs) [] 		= []
setProd []  [] 			= []

-- Helper function --
combineSet :: (Eq t, Eq t1) => Set t -> Set t1 -> Set (t, t1)
combineSet (x:xs) (y:ys) 
		| ys == [] 			= [(x,y)]
		| (y:ys) /= []  	= [(x,y)] ++ combineSet (x:xs) ys
		| otherwise 		= []
	
-- Set Partition -- 
insertInto :: Eq t => t -> Set (Set t) -> Set( Set (Set t))
insertInto x  []      		= [[[x]]]
insertInto x (xs:xss) 	= ((x:xs):xss) : map (xs:) (insertInto x xss)

partitionSet :: Eq t => Set t -> Set( Set (Set t))
partitionSet = foldr (\x r -> r >>= insertInto x) [[]]

-- Bell Number --
belNum :: Int -> Int
belNum x = length (partitionSet [1..x])

