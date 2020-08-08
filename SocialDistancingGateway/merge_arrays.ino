void merge_arrays()
{
  uint8_t ID_LB, ID_HB;
  uint8_t new_entry = 1;
  for (uint8_t g = 0; g < health_count; g++)
  {
    ID_HB = health_data[g*data_per_tag];
    ID_LB = health_data[g*data_per_tag + 1];
    for (uint8_t h = 0; h < unique_count; h++)
    {
      // If the health entry is a part of unique pair, it will not be added
      if ((ID_HB == unique_pair_data[h*data_per_tag] && ID_LB == unique_pair_data[h*data_per_tag + 1]) || (ID_HB == unique_pair_data[h*data_per_tag + 3] && ID_LB == unique_pair_data[h*data_per_tag + 4]))
      {
        new_entry = 0;
        break;
      }
    }

    if (new_entry == 1)
    {
      unique_pair_data[unique_count*data_per_tag] = ID_HB;
      unique_pair_data[unique_count*data_per_tag+1] = ID_LB;
      unique_pair_data[unique_count*data_per_tag+2] = 0;
      unique_pair_data[unique_count*data_per_tag+3] = 0;
      unique_pair_data[unique_count*data_per_tag+4] = health_data[g*data_per_tag + 4]; // Battery
      unique_pair_data[unique_count*data_per_tag+5] = health_data[g*data_per_tag + 5]; // RSSI
      unique_pair_data[unique_count*data_per_tag+6] = health_data[g*data_per_tag + 6]; // Alert
      unique_count++;
    }
  }
}
