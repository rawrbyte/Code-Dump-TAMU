-- CSCE 314 Homework Assignment #1 // 304-501 // Raymond Zhu // 923008555
import Data.Char	(isAlpha, isLower, isUpper, toLower, isDigit, isHexDigit, isOctDigit, isSpace, ord, chr, digitToInt)

-- 1 --
increaseTen :: Num a => a -> a;
increaseTen x = x + 10;

-- 2 --
-- http://learnyouahaskell.com/making-our-own-types-and-typeclasses --
circleArea :: Float -> Float;
circleArea x = pi * x^2;

-- 3 --
midList :: [a] -> [a];
midList [] = [];
midList ls = reverse(tail(reverse(tail ls)));

-- 4 --
countdownList :: Enum a => a -> a -> [a];
countdownList x y = reverse([x..y]);

-- 5 --
isRight :: Float -> Float -> Float -> Bool;
isRight x y z = ((x^2 + y^2) == z^2);

-- 6 -- 
multComplex :: (Int , Int) -> (Int , Int) -> (Int , Int);
multComplex (w, x) (y, z) = (((w*y) - (x*z)), ((w*z) + (x*y)));

-- 7 --
--https://haskell101.wordpress.com/2008/02/03/count-matches-in-a-list/ --
countChar :: Char -> String -> Int;
countChar y [] = 0;
countChar y z 
           | y == head z = 1+(countChar y (tail z))
           | otherwise = countChar y (tail z)

-- 8 --
-- http://stackoverflow.com/questions/6270214/haskell-list-of-tuples-to-list --
getFirsts :: [(t, t)] -> [t];
getFirsts ((a,b):xs) = a : getFirsts xs;
getFirsts _ = [];

-- 9 --
halfList :: [a] -> [a];
halfList (l:[]) = [];
halfList (x) = head(tail x) : halfList (tail (tail x));


-- 10 --
uppercaseList :: String -> [(Bool, Bool, Bool)];
uppercaseList (x:xs) = (isUpper (x), isLower (x), isDigit (x)) : uppercaseList (xs);
uppercaseList _ = []

-- Alternating Series --
neg_one :: Num a => [a] -> [a];
neg_one [] = [];
neg_one [x] =[x];
neg_one (x:xs) = x : (-1 * head xs) : neg_one (tail xs);
altSeries :: Num a =>[a] -> a;
altSeries xs = sum(neg_one(xs));

-- Marking Duplicates --
compareDups :: (Char, [Char]) -> Bool;
compareDups (x,xs)
		| xs == [] = False
		| x == head(xs) = True
		| length xs == 0 = False
		| otherwise = compareDups (x,tail(xs))
						
markDups :: [Char] -> [Char];
markDups xs 
		| xs == [] = []
		| (compareDups(last(xs), init(xs))) == True = markDups(init(xs)) ++ ['_']
		| otherwise = markDups(init(xs)) ++ [last(xs)]

-- Folding Strips of Paper --
insert 0 y xs = y:xs;
insert n y [] = [];
insert n y xs
		| length xs < n = xs
		| otherwise = take n xs ++ [y] ++ insert n y (drop n xs)   

count x 
		| x == 0 = []
		| x == 1 = ['v']
		| x == 2 = ['m','v','v']
		| x >= 1 = 'm' : (insert 1 'v' (fold (x-1)))
		| otherwise = "fail"
				 
checker xs 
		| xs == [] = []
		| length(xs) == 1 = xs
		| (head(take 2 xs)) == 'm' = (take 2 xs) ++ checker('v' : (drop 3 xs))
		| (head(take 2 xs)) == 'v' = (take 2 xs) ++ checker('m' : (drop 3 xs))
		| otherwise = ['f','a','i','l']
						 
fold :: Int -> String;
fold x = checker(count x);

-- Ancient Multiplication --
myMult :: (Integral a) => a -> a -> a;
myMult x y = getProduct(unzip(removeEven([(x, y)] ++ doubleHalf x y)))

getProduct :: (Integral a) => ([a], [a]) -> a;
getProduct (a, []) = 0
getProduct (a, b) = head b + getProduct(a, (tail b))

removeEven :: (Integral a) => [(a, a)] -> [(a,a)];
removeEven ((a,b):xs) 
		| ((a,b):xs) == [] = []
		| (mod a 2) == 0 = removeEven (xs)
		| (mod a 2) /=  0 = [(a,b)] ++ removeEven (xs)
		| otherwise = []
removeEven _ = []

doubleHalf :: (Integral a) => a -> a -> [(a,a)];
doubleHalf x y
		| x <= 1 = []
		| x > 1 = [(quot x 2, y*2)] ++ (doubleHalf (quot x 2) (y*2))
		| otherwise = init[(x,y)]
