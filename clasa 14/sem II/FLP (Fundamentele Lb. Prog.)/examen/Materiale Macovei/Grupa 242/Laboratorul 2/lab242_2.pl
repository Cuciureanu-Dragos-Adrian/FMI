% fib / 2
% fib (+N, -Res).

fib(0, 1).
fib(1, 1).
fib(N, Res) :-
	N1 is N - 1,
	N2 is N - 2,
	fib(N1, Res1),
	fib(N2, Res2),
	Res is Res1 + Res2.

% square / 2 
% primeste dimensiunea unei matrice si un caracter 


% squareAux(+DimMatr, +IndexLinie, +IndexColoana, +Ch).
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

square(N, Ch) :-
	squareAux(N, 1, 1, Ch).

cls :- write('\33\[2J').

%element_of / 2
%element_of(+Elem, +List).

element_of(H, [H | _]).
element_of(H, [_ | T]) :-
	element_of(H, T).

concat_lists([], L, L).
concat_lists([H | L1], L2, [H | L3]) :-
	concat_lists(L1, L2, L3).


% all_a/1 
% returneaza true daca toate elementele din lista sunt a 

all_a([a]).
all_a([a | T]) :- all_a(T).

% trans_a_b/2
% transforma o lista de a-uri intr-o lista de b-uri 

trans_a_b([a], [b]).
trans_a_b([a | T1], [b | T2]) :- trans_a_b(T1, T2).

% scalarMult / 3
% scalarMult(+Scalar, +ListaInput, -ListaOutput).
% scalarMult(3, [1,2,3], X).
% X = [3, 6, 9].

scalarMult(_, [], []).
scalarMult(Scalar, [HI | TI], [HO | TO]) :-
	HO is Scalar * HI,
	scalarMult(Scalar, TI, TO).

% dot / 3 
% dot(+List1, +List2, Res).
% dot([1,2,3],[4,5,6],Res).
% Res = 32
% produsul scalar este suma produsului pe componente 

dot([],[],0).
dot([H1 | T1], [H2 | T2], Res) :-
	dot(T1, T2, ResTail),
	Res is ResTail + H1 * H2.

% max / 2 
% max(+List, -Max).

max([], 0).
max([X], X).
max([H | T], Max) :-
	max(T, TailMax),
	H > TailMax,
	Max = H.
max([H | T], Max) :-
	max(T, TailMax),
	H =< TailMax,
	Max = TailMax.

% palindrome / 1 

palindrome(X) :- reverse(X, X).

% reverse_of / 2
% reverse_of(+List, -ListInversata).

reverse_of([], L, L).
reverse_of([H | T], ListTemp, ListRes) :-
	reverse_of(T, [H | ListTemp], ListRes).

reverse_of(L, LR) :-
	reverse_of(L, [], LR).

palindrome_of(X) :- reverse_of(X, X).

% remove_duplicates / 2
% pastreaza o singura aparitie a elementelor in lista
% remove_duplicates(+LI, -LO).

remove_duplicates([], []).
remove_duplicates([H | T], Res) :-
	member(H, T),
	remove_duplicates(T, Res).
remove_duplicates([H | T], [H | TailRes]) :-
	not(member(H, T)),
	remove_duplicates(T, TailRes).