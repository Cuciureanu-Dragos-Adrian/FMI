% ancestor_of / 2 

%fib/2
%fib(+I,-R).
fib(0, 1).
fib(1, 1).
fib(N, R) :-
	N1 is N - 1,
	N2 is N - 2,
	fib(N1, R1),
	fib(N2, R2),
	R is R1 + R2.

cls :- write('\33\[2J').

% square / 2 
% square(+Dim, +Ch).

% squareLine(0, _) :- nl.
% squareLine(N, Ch) :-
%	write(Ch),
%	N1 is N - 1,
%	squareLine(N1, Ch).

% squareAux(N, N, _) :- nl.
% squareAux(N, I, Ch) :-
%	squareLine(N, Ch),
%	I1 is I + 1,
%	squareAux(N, I1, Ch).

% square(N, Ch) :- squareAux(N, 0, Ch).

% squareAux(+Dim, +IndexLinii, +IndexColoane, +ChDeScris).

squareAux(N, N, N, Ch) :-
	write(Ch).

squareAux(N, I, N, Ch) :-
	write(Ch),
	nl,
	I1 is I + 1,
	squareAux(N, I1, 1, Ch).

squareAux(N, I, J, Ch) :-
	write(Ch),
	J1 is J + 1,
	squareAux(N, I, J1, Ch).

square(N, Ch) :- squareAux(N, 1, 1, Ch).

% Liste 

% element_of / 2 
% element_of(+List, +Element)

element_of([H | _], H).
element_of([_ | T], Element) :- 
	element_of(T, Element).


% concatenarea listelor

% concat_lists(+L1, +L2, -LAppend).

concat_lists([], L2, L2).
concat_lists([H1 | L1], L2, [H1 | L3]) :- 
	concat_lists(L1, L2, L3).

% sa se defineasca un predicat care sa calculeze lungimea unei liste

length_list([], 0).
length_list([_ | T], Res) :-
	length_list(T, Res1),
	Res is Res1 + 1.

% all_a / 1 
% verificam daca in lista sunt doar elemente a 

all_a([a]).
all_a([a | T]) :- all_a(T).

% trans_a_b/2 
% se va transforma lista de a-uri intr-o lista de b-uri 
% trans_a_b(+LInput, -LOutput).

trans_a_b([a], [b]).
trans_a_b([a | T1], [b | T2]) :- trans_a_b(T1, T2).

% scalarMult / 3 
% scalarMult(+Scalar, +Lista, -ProdusulScalar).
% scalarMult(3, [1, 2, 3], X). 
% X = [3, 6, 9.

scalarMult(_, [], []).
scalarMult(Scalar, [HInput | TInput], [HOutput | TOutput]) :-
	HOutput is Scalar * HInput,
	scalarMult(Scalar, TInput, TOutput).

% dot / 3 
% produsul scalar dintre doi vectori 
% se garanteaza ca lungimile listelor care descriu vectorii sunt egale 
% dot([1,2,3], [4,5,6], X).
% X = 32 

dot([], [], 0).
dot([H1 | T1], [H2 | T2], R) :-
	dot(T1, T2, RT),
	R is RT + H1 * H2.

% max / 2
% sa se calculeze maximul elementelor dintr-o lista

max([], 0).
max([H], H).

max([H | T], Max) :-
	max(T, TailMax),
	H > TailMax,
	Max = H. 

max([H | T], Max) :-
	max(T, TailMax),
	H =< TailMax,
	Max = TailMax.

% palindrome / 1
% verificam daca o lista este palindrom 
% reverse deja implementat

palindrome(X) :- reverse(X, X).

% trebuie sa definim noi functia reverse
% reverse_of / 2 
% reverse_of(+List, -ListResult).

reverse_of(List, ListResult) :-
	reverse_of(List, [], ListResult).

reverse_of([], List, List).
reverse_of([H | T], ListAux, ListResult) :-
	reverse_of(T, [H | ListAux], ListResult).

palindrome_of(X) :- reverse_of(X, X).

% remove_duplicates / 2 
% sterge duplicatele din prima lista si le returneaza in a doua lista
% remove_duplicates([a, a, b, a, c], X).
% returneaza X = [a, b, c].

remove_duplicates([], []).
remove_duplicates([H | T], LR) :-
	member(H, T),
	remove_duplicates(T, LR).

remove_duplicates([H | T], [H | TR]) :-
	not(member(H, T)),
	remove_duplicates(T, TR).

% replace / 4 
replace([], _, _, []).
replace([H | T], H, Y, [Y | TO]) :- 
	replace(T, H, Y, TO).
replace([H | T], X, Y, [H | TO]) :-
	replace(T, X, Y, TO).