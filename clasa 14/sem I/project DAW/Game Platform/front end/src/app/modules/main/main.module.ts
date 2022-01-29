import { NgModule } from '@angular/core';
import { CommonModule } from '@angular/common';
import { MainRoutingModule } from './main-routing.module';
import { GamesComponent } from './games/games.component';
import { CompaniesComponent } from './companies/companies.component';
import { EventsComponent } from './events/events.component';
import { MaterialModule } from '../material/material.module';
import { HomeComponent } from './home/home.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { IndexPipe } from '../pipes/index.pipe';


@NgModule({
  declarations: [
    GamesComponent,
    CompaniesComponent,
    EventsComponent,
    HomeComponent,
    DashboardComponent,
    IndexPipe,
  ],
  imports: [
    CommonModule,
    MainRoutingModule,
    MaterialModule,
  ],
  exports: [
    IndexPipe,
  ],
})
export class MainModule { }
