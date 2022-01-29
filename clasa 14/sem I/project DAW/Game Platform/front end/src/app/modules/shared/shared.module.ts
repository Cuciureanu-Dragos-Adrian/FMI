import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { AddEditGameComponent } from './add-edit-game/add-edit-game.component';
import { MaterialModule } from '../material/material.module';
import { AddEditCompanyComponent } from './add-edit-company/add-edit-company.component';



@NgModule({
  declarations: [
    AddEditGameComponent,
    AddEditCompanyComponent
  ],
  imports: [
    CommonModule,
    MaterialModule,
  ],
  entryComponents:[
    AddEditGameComponent
  ]
})
export class SharedModule { }
