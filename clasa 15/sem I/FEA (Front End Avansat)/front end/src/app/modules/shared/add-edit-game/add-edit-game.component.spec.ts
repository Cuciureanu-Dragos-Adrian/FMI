import { ComponentFixture, TestBed } from '@angular/core/testing';

import { AddEditGameComponent } from './add-edit-game.component';

describe('AddEditGameComponent', () => {
  let component: AddEditGameComponent;
  let fixture: ComponentFixture<AddEditGameComponent>;

  beforeEach(async () => {
    await TestBed.configureTestingModule({
      declarations: [ AddEditGameComponent ]
    })
    .compileComponents();
  });

  beforeEach(() => {
    fixture = TestBed.createComponent(AddEditGameComponent);
    component = fixture.componentInstance;
    fixture.detectChanges();
  });

  it('should create', () => {
    expect(component).toBeTruthy();
  });
});
