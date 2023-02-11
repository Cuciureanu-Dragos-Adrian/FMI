import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { IndexPipe } from './index.pipe';
import { ColonPipe } from './colon.pipe';



@NgModule({
  declarations: [
    IndexPipe,
    ColonPipe
  ],
  imports: [
    CommonModule
  ]
})
export class PipesModule { }
