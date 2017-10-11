# OntoTeamCompiler

MiniJava compliler project based on [Andrew W. Appel book](https://www.cs.princeton.edu/~appel/modern/java/).

## Features
- Lexical analysis with *flex*
- Syntactic analysis with *bison*
- Abstract Syntax Tree (AST) generation
- Tree visualization with *dot*
- Semantic analysis: symbol tables and typechecking
- Intermediate Representation Tree (IRT) generation
- To be continued...

## Examples

Consider the following code in MiniJava:

```Java
class Factorial{
    public static void main(String[] a){
  System.out.println(new Fac().ComputeFac(10));
    }
}
class Fac {
    public int ComputeFac(int num){
  int num_aux ;
  if (num < 1)
      num_aux = 1 ;
  else 
      num_aux = num * (this.ComputeFac(num-1)) ;
  return num_aux ;
    }
}
```

- AST
![AST](https://github.com/alexeyqu/OntoTeamCompiler/blob/jiver/jive/test/good_results/Factorial.java/AST_AbstractSyntaxTree.png)

- Class table

```
Class Fac
  Fields:
  Methods:
    Method ComputeFac with return Type int
	Args:
		Arg num of Type int
	Vars:
		Var num_aux of Type int
---
Class Factorial
  Fields:
  Methods:
  Method main with return Type void
	  Args:
		  Arg a of Type String[]
	  Vars:
```

- IRT 
![IRT](https://github.com/alexeyqu/OntoTeamCompiler/blob/jiver/jive/test/good_results/Factorial.java/IR_IRTree.png)
