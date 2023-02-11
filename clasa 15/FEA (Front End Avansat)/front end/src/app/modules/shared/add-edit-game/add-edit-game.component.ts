import { Component, Inject, OnInit } from '@angular/core';
import { AbstractControl, FormControl, FormGroup } from '@angular/forms';
import { MatDialogRef, MAT_DIALOG_DATA } from '@angular/material/dialog';
import { GamesService } from 'src/app/services/games.service';


@Component({
  selector: 'app-add-edit-game',
  templateUrl: './add-edit-game.component.html',
  styleUrls: ['./add-edit-game.component.scss']
})
export class AddEditGameComponent implements OnInit {

  public gameForm: FormGroup = new FormGroup(
    {
    id: new FormControl(''), 
    name: new FormControl(''),
    releaseDate: new FormControl(''),
    review: new FormControl(0),
    price: new FormControl(0),
    }
  );
  public title : any;
  public buttonTitle : any;

  constructor(
    @Inject(MAT_DIALOG_DATA) public data : any,
    private gamesService: GamesService,
    public dialogRef: MatDialogRef<AddEditGameComponent>, 
  ) { 
    console.log(this.data);
    if(data.game){
      this.title = 'Edit Game';
      this.buttonTitle = "Edit";
      this.gameForm.patchValue(this.data.game);
    }
    else{
      this.title = 'Add Game';
      this.buttonTitle = "Add";
    }
  }

  //getters
  get id(): AbstractControl
  {
    return this.gameForm.get('id')!;
  }

  get name(): AbstractControl
  {
    return this.gameForm.get('name')!;
  }

  get releaseDate(): AbstractControl
  {
    return this.gameForm.get('releaseDate')!;
  }

  get review(): AbstractControl
  {
    return this.gameForm.get('review')!;
  }

  get price(): AbstractControl
  {
    return this.gameForm.get('price')!;
  }

  ngOnInit(): void {
  }

  public addGame(): void{
    if(this.buttonTitle == "Add")
    {
      this.gamesService.addGame(this.gameForm.value).subscribe({
        next:(result : any) => {
          this.dialogRef.close(result);
        },
        error:(error : any) => {
          console.error(error);
        },
      });
    }
    else
    {
      this.gamesService.editGame(this.gameForm.value).subscribe({
        next:(result : any) => {
          this.dialogRef.close(result);
        },
        error:(error : any) => {
          console.error(error);
        },
      });
    }
  }
}
