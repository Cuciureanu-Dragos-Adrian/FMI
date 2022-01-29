import { Component, OnDestroy, OnInit } from '@angular/core';
import { MatDialog, MatDialogConfig } from '@angular/material/dialog';
import { Router } from '@angular/router';
import { Observable, Subscription } from 'rxjs';
import { DataService } from 'src/app/services/data.service';
import { GamesService } from 'src/app/services/games.service';
import { AddEditGameComponent } from '../../shared/add-edit-game/add-edit-game.component';

interface filterOption {
  value: string;
  viewValue: string;
}

@Component({
  selector: 'app-games',
  templateUrl: './games.component.html',
  styleUrls: ['./games.component.scss']
})
export class GamesComponent implements OnInit, OnDestroy {

  public subscription!: Subscription;
  public loggedUser : any;
  public panelOpenState = false;
  public games: any = [];
  //public games: Observable<any> = [];
  public filterOptions : filterOption[]  = [
    {value: 'aa', viewValue: 'Alphabetically ascending'},
    {value: 'ad', viewValue: 'Alphabetically descending'},
    {value: 'ra', viewValue: 'Review ascending'},
    {value: 'rd', viewValue: 'Review descending'},
  ]
  public selectedFilter : any = "nothing";

  constructor(
    private router: Router,
    private dataService: DataService,
    private gamesService: GamesService,
    public dialog: MatDialog,
    ) { }

  ngOnInit(): void {
    this.subscription = this.dataService.currentUser.subscribe(user => this.loggedUser = user)

    if (this.selectedFilter == "nothing")
    {
      this.gamesService.getGames().subscribe({
      next:(result : any) => {
        this.games = result;
      },
      error:(error : any) => {
        console.error(error);
      },
    })}
  }

  public filterAccordion(): void{
    if (this.selectedFilter == "aa")
    {
      this.gamesService.getGamesAlphabeticalAscending().subscribe({
      next:(result : any) => {
        this.games = result;
      },
      error:(error : any) => {
        console.error(error);
      },
    })}

    if (this.selectedFilter == "ad")
    {
      this.gamesService.getGamesAlphabeticalDescending().subscribe({
      next:(result : any) => {
        this.games = result;
      },
      error:(error : any) => {
        console.error(error);
      },
    })}

    if (this.selectedFilter == "ra")
    {
      this.gamesService.getGamesReviewAscending().subscribe({
      next:(result : any) => {
        this.games = result;
      },
      error:(error : any) => {
        console.error(error);
      },
    })}

    if (this.selectedFilter == "rd")
    {
      this.gamesService.getGamesReviewDescending().subscribe(
        {
          next:(result : any) => {
            this.games = result;
          },
          error:(error : any) => {
            console.error(error);
          },
        }
      )}
  }

  public openModal(game? : any): void {
    const data = {
      game
    }
    const dialogConfig = new MatDialogConfig();
    dialogConfig.width = '300px';
    dialogConfig.height = '500px';
    dialogConfig.data = data;

    const dialogRef = this.dialog.open(AddEditGameComponent, dialogConfig);
    dialogRef.afterClosed().subscribe({
      next:(result) => {
        if(result){
          this.games = result;
          this.games = this.gamesService.getGames();
          //this.games = [...this.games];
          this.gamesService.getGames().subscribe({
            next:(result : any) => {
              this.games = result;
            },
            error:(error : any) => {
              console.error(error);
            },
          })
        }
      },
      error:(error) => {
        console.log(error);
      }
    })
  }
  
  public addNewGame(): void{
    this.openModal();
  }

  public editGame(game : any): void{
    this.openModal(game);
  }

  public deleteGame(game : any): void{
    this.gamesService.deleteGame(game).subscribe({
      next:(result) =>{
        this.games = result;
      },
      error:(error) => {
        console.log(error);
      }
    })
  }

  ngOnDestroy(): void {
      this.subscription.unsubscribe();
  }

  public logout(): void
  {
    localStorage.setItem('Role', 'Anonymus');
    this.router.navigate(['/login']);
  }
}
