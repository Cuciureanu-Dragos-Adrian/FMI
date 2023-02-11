import { Component, OnInit } from '@angular/core';
import { ActivatedRoute } from '@angular/router';
import { Subscription } from 'rxjs';
import { CompaniesService } from 'src/app/services/companies.service';

@Component({
  selector: 'app-company',
  templateUrl: './company.component.html',
  styleUrls: ['./company.component.scss']
})
export class CompanyComponent implements OnInit {

  public subscription!: Subscription;
  public id : any;
  public company : any = {
    name: '',
    headquarter: '',
    country: '',
    city: '',
    games: '',
  };

  constructor(
    private router: ActivatedRoute,
    private companiesService: CompaniesService,
  ) { }

  ngOnInit(): void {
    this.subscription = this.router.params.subscribe(params => {
      this.id = params['id'];

      if(this.id){
        this.getCompany();
      }
    })
  }

  public getCompany(): void{
    this.companiesService.getCompanyById(this.id).subscribe({
      next:(result) =>{
        console.log(result);
        this.company = result;
      },
      error:(error) => {
        console.log(error);
      }
    });
  }
}
