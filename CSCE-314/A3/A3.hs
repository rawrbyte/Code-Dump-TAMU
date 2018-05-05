-- CSCE 314 Homework Assignment  #3 // 304-501 // Raymond Zhu // 923008555
--------------------------------------------------------------------------------------------------------
-- Data types and type classes -- 
data Tree a b = Branch b (Tree a b) (Tree a b)
              | Leaf a
			  
instance (Show a, Show b) => Show (Tree a b) where show t = showIndent "  " t where
showIndent indent (Leaf x) = indent ++ show x; showIndent indent (Branch n l r) = indent ++ (show n) ++ "\n" ++ (showIndent indentmore l) ++ "\n" ++ (showIndent indentmore r) where indentmore = indent ++ "   "

preorder  :: (a -> c) -> (b -> c) -> Tree a b -> [c]
postorder :: (a -> c) -> (b -> c) -> Tree a b -> [c]
inorder   :: (a -> c) -> (b -> c) -> Tree a b -> [c]

preorder a b (Leaf n) = [x] where x = a n
preorder a b (Branch n l r) = [x] ++ y ++ z where x = b n; y = preorder a b l; z = preorder a b r

postorder a b (Leaf n) = [x] where x = a n
postorder a b (Branch n l r) = x ++ y ++ [z] where x = postorder a b l; y = postorder a b r; z = b n

inorder a b (Leaf n) = [x] where x = a n
inorder a b (Branch n l r) = x ++ [y] ++ z where x = inorder a b l; y = b n; z = inorder a b r
--------------------------------------------------------------------------------------------------------
-- Evaluating Expressions -- 
data E = IntLit Int
       | BoolLit Bool
       | Plus E E
       | Minus E E
       | Multiplies E E
	   | Exponentiate E E
       | Divides E E
       | Equals E E
         deriving (Eq, Show)

eval :: E -> E
eval (IntLit i) = IntLit i
eval (Plus a b) = IntLit $ asInt (eval a) + asInt (eval b)
eval (Minus a b) = IntLit $ asInt (eval a) - asInt (eval b)
eval (Multiplies a b) = IntLit $ asInt (eval a) * asInt (eval b)
eval (Exponentiate a b) = IntLit $ asInt (eval a) ^ asInt (eval b)
eval (Divides a b) = IntLit $ asInt (eval a) `div` asInt (eval b)
eval (BoolLit n) = BoolLit n
eval (Equals a b) = BoolLit $ eval a == eval b

asInt :: E -> Int
asInt (IntLit i) = i

program = Equals 
            (Plus (IntLit 1) (IntLit 2))
            (Minus
             (IntLit 5)
             (Minus (IntLit 3) (IntLit 1)))

program' = Equals
            (Plus (IntLit 1) (IntLit 2))
            (Minus
              (IntLit 5)
              (Exponentiate (IntLit 3) (IntLit 1)))

log2Sim :: E -> E
log2Sim (IntLit a) | (2^(e) == a) = IntLit e
		             where e = truncate(logBase 2.0 (fromIntegral a))


log2Sim (Multiplies (a)(b)) = (Plus (log2Sim (a))(log2Sim (b)))
log2Sim (Divides (a)(b)) = (Minus (log2Sim (a))(log2Sim (b)))
log2Sim (Exponentiate (a)(b)) = (Multiplies (b) (log2Sim (a)))
log2Sim (Equals (a)(b)) = Equals (log2Sim(a))(log2Sim(b))
log2Sim (BoolLit n) = BoolLit n
--------------------------------------------------------------------------------------------------------


