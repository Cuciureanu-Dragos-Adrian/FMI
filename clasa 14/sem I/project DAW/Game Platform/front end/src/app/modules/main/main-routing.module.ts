import { NgModule } from '@angular/core';
import { RouterModule, Routes } from '@angular/router';
import { CompaniesComponent } from './companies/companies.component';
import { DashboardComponent } from './dashboard/dashboard.component';
import { EventsComponent } from './events/events.component';
import { GamesComponent } from './games/games.component';
import { HomeComponent } from './home/home.component';

const routes: Routes = [
  {
    path: 'dashboard',
    component: DashboardComponent,
  
    children: [
      {
        path: '',
        redirectTo: 'home',
      },
      {
        path: 'home',
        component: HomeComponent,
      },
      {
        path: 'games',
        component: GamesComponent
      },
      {
        path: 'companies',
        component: CompaniesComponent,
      },
      {
        path: 'events',
        component: EventsComponent,
      },
      {
        path: '**',
        redirectTo: 'games',
      }]
    }
];

@NgModule({
  imports: [RouterModule.forChild(routes)],
  exports: [RouterModule]
})
export class MainRoutingModule { }
